#include "spirv-cross/spirv_cross_compiler.hpp"
#include <iostream>

namespace ris_shader_toolkit {

	SpirVCrossCompiler::SpirVCrossCompiler() {
		glslVersionMap = {
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
	}

	void SpirVCrossCompiler::applyReplaceStageInputNameRule(
		spirv_cross::CompilerGLSL& compiler,
		spirv_cross::ShaderResources& shaderResources,
		ReplaceStageInputNameRule* rule) {


		// By default, names have "input_" prefix, we will remove it here
		// Rename vertex inputs from "input_{name}" to just "{name}"
		for (auto& input : shaderResources.stage_inputs)
		{
			std::string name = compiler.get_name(input.id);
			std::string newName = name;

			// Remove "input_" prefix if it exists
			if (name.rfind("input.", 0) == 0) // starts with "input_"
			{
				newName = name.substr(6); // remove first 6 chars
			}

			if (rule != nullptr) {
				// Apply prefix from rule
				newName = rule->getPrefix() + newName;
			}

			compiler.set_name(input.id, newName);
		}
	}

	void SpirVCrossCompiler::applyReplaceStageOutputNameRule(
		spirv_cross::CompilerGLSL& compiler,
		spirv_cross::ShaderResources& shaderResources,
		ReplaceStageOutputNameRule* rule) {

		// By default, names have "entryPointParam_" prefix, we will remove it here
		// Rename vertex inputs from "entryPointParam_{entryName}.{name}" to just "{entryName}.{name}"
		for (auto& input : shaderResources.stage_outputs)
		{
			std::string name = compiler.get_name(input.id);
			std::string newName = name;

			// Remove "input_" prefix if it exists
			if (name.rfind("entryPointParam_", 0) == 0) // starts with "entryPointParam_"
			{
				newName = name.substr(16); // remove first 16 chars
			}

			if (rule != nullptr) {

				if(rule->getTrimEntryPointName()) {
					// Further trim entry point name if exists
					size_t dotPos = newName.find('.');
					if (dotPos != std::string::npos) {
						newName = newName.substr(dotPos + 1); // remove up to and including the dot
					}
				}

				// Apply prefix from rule
				newName = rule->getPrefix() + newName;
			}

			compiler.set_name(input.id, newName);
		}
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

	SpirVCrossCompileResult SpirVCrossCompiler::compile(
		const std::string& filePath, GlslProfile profile,
		ReplaceStageInputNameRule* replaceStageInputNameRule,
		ReplaceStageOutputNameRule* replaceStageOutputNameRule
	) {

		// Load SPIR-V
		std::vector<uint32_t> spirv = fileReader.readAsU32(filePath);
		return compile(spirv, profile, replaceStageInputNameRule);
	}

	SpirVCrossCompileResult SpirVCrossCompiler::compile(
		const std::vector<uint32_t>& spirv, GlslProfile profile,
		ReplaceStageInputNameRule* replaceStageInputNameRule,
		ReplaceStageOutputNameRule* replaceStageOutputNameRule
	) {
		// Load SPIR-V
		try {
			spirv_cross::CompilerGLSL compiler(spirv);
			// Set GLSL options
			spirv_cross::CompilerGLSL::Options options;
			options.version = glslVersionMap[profile];
			options.force_zero_initialized_variables = false;
			if (profile == GlslProfile::GLES_300 || profile == GlslProfile::GLES_310 || profile == GlslProfile::GLES_320) {
				options.es = true;
			}

			compiler.set_common_options(options);

			// Get shader resources
			spirv_cross::ShaderResources resources = compiler.get_shader_resources();

			applyReplaceStageInputNameRule(compiler, resources, replaceStageInputNameRule);
			applyReplaceStageOutputNameRule(compiler, resources, replaceStageOutputNameRule);
			handleImageAndSamplersGlsl(compiler, resources);

			// Compile to GLSL
			std::string glslSource = compiler.compile();
			return SpirVCrossCompileResult(true, glslSource, "");
		}
		catch (const std::exception& e) {
			return SpirVCrossCompileResult(false, "", e.what());
		}
	}
} // namespace ris_shader_toolkit