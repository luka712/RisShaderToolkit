#include "glslang/glslang_compiler.hpp"

namespace ris_shader_toolkit
{
	GlslangCompiler::GlslangCompiler() {
		shaderStageMap = {
			{ ShaderStage::Vertex, GLSLANG_STAGE_VERTEX },
			{ ShaderStage::Fragment, GLSLANG_STAGE_FRAGMENT },
			{ ShaderStage::Compute, GLSLANG_STAGE_COMPUTE },
			//{ ShaderStage::Geometry, GLSLANG_STAGE_GEOMETRY },
			//{ ShaderStage::Hull, GLSLANG_STAGE_TESS_CONTROL },
			//{ ShaderStage::Domain, GLSLANG_STAGE_TESS_EVALUATION }
		};
	}

	GlslangCompileResult GlslangCompiler::compile(
		const std::string& filePath,
		glslang_stage_t stage)
	{
		// TODO: Validate input file

		std::string shaderSource = fileReader.read(filePath);

		const glslang_input_t input = {
			   .language = GLSLANG_SOURCE_GLSL,
			   .stage = stage,
			   .client = GLSLANG_CLIENT_VULKAN,
			   .client_version = GLSLANG_TARGET_VULKAN_1_2,
			   .target_language = GLSLANG_TARGET_SPV,
			   .target_language_version = GLSLANG_TARGET_SPV_1_5,
			   .code = shaderSource.c_str(),
			   .default_version = 100,
			   .default_profile = GLSLANG_NO_PROFILE,
			   .force_default_version_and_profile = false,
			   .forward_compatible = false,
			   .messages = GLSLANG_MSG_DEFAULT_BIT,
			   .resource = glslang_default_resource(),
		};

		glslang_shader_t* shader = glslang_shader_create(&input);

		if (!glslang_shader_preprocess(shader, &input))
		{
			std::string msg = "GLSL preprocessing failed " + filePath + "\n";
			msg += std::string(glslang_shader_get_info_log(shader)) + "\n";
			msg += std::string(glslang_shader_get_info_debug_log(shader)) + "\n";
			msg += std::string(input.code) + "\n";
			glslang_shader_delete(shader);
			return GlslangCompileResult::errorResult(msg);
		}

		if (!glslang_shader_parse(shader, &input))
		{
			std::string msg = "GLSL parsing failed " + filePath + "\n";
			msg += std::string(glslang_shader_get_info_log(shader)) + "\n";
			msg += std::string(glslang_shader_get_info_debug_log(shader)) + "\n";
			msg += std::string(glslang_shader_get_preprocessed_code(shader)) + "\n";
			glslang_shader_delete(shader);
			return GlslangCompileResult::errorResult(msg);
		}

		glslang_program_t* program = glslang_program_create();
		glslang_program_add_shader(program, shader);

		if (!glslang_program_link(program, GLSLANG_MSG_SPV_RULES_BIT | GLSLANG_MSG_VULKAN_RULES_BIT))
		{
			std::string msg = "GLSL linking failed " + filePath + "\n";
			msg += std::string(glslang_program_get_info_log(program)) + "\n";
			msg += std::string(glslang_program_get_info_debug_log(program)) + "\n";
			glslang_program_delete(program);
			glslang_shader_delete(shader);
			return GlslangCompileResult::errorResult(msg);
		}

		glslang_program_SPIRV_generate(program, stage);

		size_t size = glslang_program_SPIRV_get_size(program);
		uint32_t* words = (uint32_t*)malloc(size * sizeof(uint32_t));
		glslang_program_SPIRV_get(program, words);

		const char* spirv_messages = glslang_program_SPIRV_get_messages(program);
		if (spirv_messages)
		{
			// TODO: Log any messages from SPIR-V generation
			printf("(%s) %s\b", filePath, spirv_messages);
		}

		glslang_program_delete(program);
		glslang_shader_delete(shader);

		if (words == nullptr || size == 0)
		{
			return GlslangCompileResult::errorResult("Failed to generate SPIR-V code.");
		}

		std::string resultCode = std::string((const char*)words, size * sizeof(uint32_t));

		return GlslangCompileResult::successResult(resultCode);
	}
}

