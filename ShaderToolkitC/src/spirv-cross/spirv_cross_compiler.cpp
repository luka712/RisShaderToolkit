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

	SpirVCrossCompileResult SpirVCrossCompiler::compile(const std::vector<uint32_t>& spirv, GlslProfile profile, ShaderStage stage) {
		// Load SPIR-V
		try {
			spirv_cross::CompilerGLSL compiler(spirv);

			// Set GLSL options
			spirv_cross::CompilerGLSL::Options options;
			options.version = _glslVersionMap[profile];
			options.force_zero_initialized_variables = false;
			if (profile == GlslProfile::GLES_300 || profile == GlslProfile::GLES_310 || profile == GlslProfile::GLES_320) {
				options.es = true;
			}

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