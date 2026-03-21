#include "spirv-cross/spirv_cross_compiler.hpp"
#include <iostream>
#include <spdlog/spdlog.h>

namespace ris_shader_toolkit {

	SpirVCrossCompiler::SpirVCrossCompiler() {
		_glslVersionMap = {
			{ GlslProfile::GLSL_330, 330 },
			{ GlslProfile::GLSL_400, 400 },
			{ GlslProfile::GLSL_410, 410 },
			{ GlslProfile::GLSL_420, 420 },
			{ GlslProfile::GLSL_430, 430 },
			{ GlslProfile::GLSL_440, 440 },
			{ GlslProfile::GLSL_450, 450 },
			{ GlslProfile::GLSL_460, 460 },
			{ GlslProfile::GLES_300, 300 },
			{ GlslProfile::GLES_310, 310 },
			{ GlslProfile::GLES_320, 320 }
		};

		_executionModelMap = {
			{ ShaderStage::Vertex, spv::ExecutionModel::ExecutionModelVertex },
			{ ShaderStage::Fragment, spv::ExecutionModel::ExecutionModelFragment },
			{ ShaderStage::Compute, spv::ExecutionModel::ExecutionModelGLCompute },
			//{ ShaderStage::Geometry, spv::ExecutionModel::ExecutionModelGeometry },
			//{ ShaderStage::Hull, spv::ExecutionModel::ExecutionModelTessellationControl },
			//{ ShaderStage::Domain, spv::ExecutionModel::ExecutionModelTessellationEvaluation }
		};
	}

	void SpirVCrossCompiler::handleImageAndSamplersGlsl(
		spirv_cross::CompilerGLSL& compiler,
		spirv_cross::ShaderResources& shaderResources) {

		// Since output of SpirV to glsl might have name such as _31, we keep name of sampler,
		// to replace that with sampler name instead.
		std::map<uint32_t, std::string> samplerIdNames;
		for (auto& sampler : shaderResources.separate_samplers)
		{
			samplerIdNames[sampler.id] = compiler.get_name(sampler.id);
		}

		compiler.build_combined_image_samplers(); // Finalize combined samplers for GLSL

		for (auto& cs : compiler.get_combined_image_samplers())
		{
			// Rename _31 to something meaningful, e.g., diffuseTexture
			compiler.set_name(cs.combined_id, samplerIdNames[cs.sampler_id]);
		}
	}

	void SpirVCrossCompiler::handleAttributes(
		spirv_cross::CompilerGLSL& vertexCompiler,
		spirv_cross::CompilerGLSL& fragmentCompiler,
		GlslProfile glslProfile,
		ShaderStage stage)
	{

		// For GLES 3.0, we need to ensure that the input/output variable names match between vertex and fragment shaders.
		// So input attribute of fragment shader should have name to corresponding output attribute of vertex shader.
		// This is required for linking shaders in GLES 3.0.
		if (glslProfile == GlslProfile::GLES_300 && stage == ShaderStage::Fragment)
		{
			std::map <uint32_t, std::string> inputIdNames;
			uint32_t location = 0;
			auto vertexShaderResources = vertexCompiler.get_shader_resources();
			for (auto& outAttr : vertexShaderResources.stage_outputs)
			{
				std::string name = outAttr.name;
				inputIdNames[location] = name;
				location++;
			}

			location = 0;
			auto fragmentShaderResources = fragmentCompiler.get_shader_resources();
			for (auto& inAttr : fragmentShaderResources.stage_inputs)
			{
				std::string name = inputIdNames[location];
				fragmentCompiler.set_name(inAttr.id, name);
				location++;
			}
		}
	}

	void SpirVCrossCompiler::handleUniforms(spirv_cross::CompilerGLSL& compiler)
	{
		auto resources = compiler.get_shader_resources();
		for (auto& ubo : resources.uniform_buffers)
		{
			spdlog::debug("UBO: " + ubo.name);

			uint32_t type_id = ubo.base_type_id;

			// If it's row major, then it applies to the whole block, otherwise we need to check each member.
			if (compiler.has_decoration(type_id, spv::DecorationRowMajor))
			{
				compiler.unset_decoration(type_id, spv::DecorationRowMajor);
				compiler.set_decoration(type_id, spv::DecorationColMajor);
				spdlog::debug("  has RowMajor decoration, changed to ColMajor");
			}
			else 
			{
				auto& type = compiler.get_type(ubo.base_type_id);
				for (uint32_t i = 0; i < type.member_types.size(); i++)
				{
					spdlog::debug("  member " + std::to_string(i));

					if (compiler.has_member_decoration(ubo.base_type_id, i, spv::DecorationRowMajor))
					{
						spdlog::debug("    has RowMajor decoration");
					}

					if (compiler.has_member_decoration(ubo.base_type_id, i, spv::DecorationColMajor))
					{
						spdlog::debug("    has ColMajor decoration");
					}

					std::cout << "\n";
				}
			}
		}
	}

	SpirVCrossCompileResult SpirVCrossCompiler::compileForLowerProfiles(const std::vector<uint32_t>& spirv, GlslProfile profile, ShaderStage stage)
	{
		// Load SPIR-V
		try {
			spirv_cross::CompilerGLSL vertexCompiler(spirv);
			spirv_cross::CompilerGLSL fragmentCompiler(spirv);

			// Default to vertex compiler, will switch to fragment compiler if stage is fragment shader.
			spirv_cross::CompilerGLSL* targetCompiler = &vertexCompiler;
			if (stage == ShaderStage::Fragment)
			{
				targetCompiler = &fragmentCompiler;
			}

			// Set GLSL options
			spirv_cross::CompilerGLSL::Options options;
			options.version = _glslVersionMap[profile];
			options.force_zero_initialized_variables = false;
			options.enable_storage_image_qualifier_deduction = true;
			if (profile == GlslProfile::GLES_300
				|| profile == GlslProfile::GLES_310
				|| profile == GlslProfile::GLES_320) {
				options.es = true;
			}

			auto entry_points = vertexCompiler.get_entry_points_and_stages();
			for (size_t i = 0; i < entry_points.size(); ++i)
			{
				auto executionModel = entry_points[i].execution_model;

				if (spv::ExecutionModel::ExecutionModelVertex == executionModel)
				{
					auto entryPointName = entry_points[i].name;
					vertexCompiler.set_entry_point(entryPointName, executionModel);
				}
				else if (spv::ExecutionModel::ExecutionModelFragment == executionModel)
				{
					auto entryPointName = entry_points[i].name;
					fragmentCompiler.set_entry_point(entryPointName, executionModel);
				}
				else
				{
					std::string msg = "Unsupported execution model: " + std::to_string(executionModel);
					spdlog::error(msg);
					return SpirVCrossCompileResult::errorResult(msg);
				}
			}

			auto vertexShaderResources = vertexCompiler.get_shader_resources();
			auto fragmentShaderResources = fragmentCompiler.get_shader_resources();

			handleImageAndSamplersGlsl(fragmentCompiler, fragmentShaderResources);
			handleAttributes(vertexCompiler, fragmentCompiler, profile, stage);
			handleUniforms(vertexCompiler);
			handleUniforms(fragmentCompiler);
			vertexCompiler.set_common_options(options);
			fragmentCompiler.set_common_options(options);

			// Compile to GLSL
			std::string glslSource = targetCompiler->compile();
			return SpirVCrossCompileResult(true, glslSource, "");
		}
		catch (const std::exception& e) {
			std::string msg = "SPIRV-Cross compilation failed: " + std::string(e.what());
			spdlog::error(msg);
			return SpirVCrossCompileResult::errorResult(msg);
		}
	}

	SpirVCrossCompileResult SpirVCrossCompiler::compile(const std::vector<uint32_t>& spirv, GlslProfile profile, ShaderStage stage) {

		if (profile == GlslProfile::GLES_300)
		{
			return compileForLowerProfiles(spirv, profile, stage);
		}

		// Load SPIR-V
		try {
			spirv_cross::CompilerGLSL compiler(spirv);

			// Set GLSL options
			spirv_cross::CompilerGLSL::Options options;
			options.version = _glslVersionMap[profile];
			options.force_zero_initialized_variables = false;
			if (profile == GlslProfile::GLES_310 || profile == GlslProfile::GLES_320) {
				options.es = true;
			}
			options.vertex.fixup_clipspace = true;

			auto entry_points = compiler.get_entry_points_and_stages();
			for (size_t i = 0; i < entry_points.size(); ++i)
			{
				auto executionModel = entry_points[i].execution_model;
				auto desiredExecutionModel = _executionModelMap[stage];

				if (desiredExecutionModel == executionModel)
				{
					auto entryPointName = entry_points[i].name;
					compiler.set_entry_point(entryPointName, executionModel);
				}
			}

			auto shaderResources = compiler.get_shader_resources();
			handleImageAndSamplersGlsl(compiler, shaderResources);
			compiler.set_common_options(options);

			// Compile to GLSL
			std::string glslSource = compiler.compile();

			return SpirVCrossCompileResult(true, glslSource, "");
		}
		catch (const std::exception& e) {
			spdlog::error("SPIRV-Cross compilation failed: {}", e.what());
			return SpirVCrossCompileResult(false, "", e.what());
		}
	}
} // namespace ris_shader_toolkit