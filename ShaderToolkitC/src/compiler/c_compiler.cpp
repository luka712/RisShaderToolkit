#include "compiler/c_compiler.hpp"

void* create_compiler()
{
	return new ris_shader_toolkit::Compiler();
}

char* get_last_error_message()
{
	return lastErrorMessage.empty() ? nullptr : const_cast<char*>(lastErrorMessage.c_str());
}

void* compile_slang_to_glsl(
	void* compilerPtr,
	const char* inputFilePath,
	int profile,           // GlslProfile as int
	int shaderStage,       // ShaderStage as int
	const char* entryPointPtr,
	void* inputRulePtr,
	void* outputRulePtr
)
{
	if (compilerPtr == nullptr)
	{
		return errorResult("Compiler instance is null.");
	}

	ris_shader_toolkit::Compiler* compiler = static_cast<ris_shader_toolkit::Compiler*>(compilerPtr);

	if (inputFilePath == nullptr)
	{
		return errorResult("Input file path or entry point is null.");
	}

	ris_shader_toolkit::GlslProfile glslProfile = static_cast<ris_shader_toolkit::GlslProfile>(profile);
	ris_shader_toolkit::ShaderStage stage = static_cast<ris_shader_toolkit::ShaderStage>(shaderStage);

	// Use "main" as default entry point if none is provided
	std::string entryPoint = (entryPointPtr != nullptr) ? std::string(entryPointPtr) : "main";
	ris_shader_toolkit::ReplaceStageInputNameRule* inputRule = nullptr;
	if (inputRulePtr != nullptr)
	{
		inputRule = static_cast<ris_shader_toolkit::ReplaceStageInputNameRule*>(inputRulePtr);
	}
	ris_shader_toolkit::ReplaceStageOutputNameRule* outputRule = nullptr;
	if (outputRulePtr != nullptr)
	{
		outputRule = static_cast<ris_shader_toolkit::ReplaceStageOutputNameRule*>(outputRulePtr);
	}

	ris_shader_toolkit::CompileResult result = compiler->compileSlangToGlsl(
		std::string(inputFilePath),
		glslProfile, stage,
		std::string(entryPoint),
		inputRule, outputRule
	);


	return c_to_cpp_CompileResult(result);
}

void free_compiler(void* compilerPtr)
{
	ris_shader_toolkit::Compiler* compiler = static_cast<ris_shader_toolkit::Compiler*>(compilerPtr);
	delete compiler;
}


