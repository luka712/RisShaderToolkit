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
	c_ReplaceStageInputNameRule* inputRulePtr,
	c_ReplaceStageOutputNameRule* outputRulePtr
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
	ris_shader_toolkit::ReplaceStageInputNameRule* inputRule = c_to_cpp_ReplaceStageInputNameRule(inputRulePtr);
	ris_shader_toolkit::ReplaceStageOutputNameRule* outputRule = c_to_cpp_ReplaceStageOutputNameRule(outputRulePtr);

	ris_shader_toolkit::CompileResult result = compiler->compileSlangToGlsl(
		std::string(inputFilePath),
		glslProfile, stage,
		std::string(entryPoint),
		inputRule, outputRule
	);

	delete inputRule;
	delete outputRule;

	return c_to_cpp_CompileResult(result);
}


void* compile_slang_source_code_to_glsl(
	void* compilerPtr,
	const char* slangSourceCode,
	int profile,           // GlslProfile as int
	int shaderStage,       // ShaderStage as int
	const char* entryPointPtr,
	c_ReplaceStageInputNameRule* inputRulePtr,
	c_ReplaceStageOutputNameRule* outputRulePtr
)
{
	if (compilerPtr == nullptr)
	{
		return errorResult("Compiler instance is null.");
	}

	ris_shader_toolkit::Compiler* compiler = static_cast<ris_shader_toolkit::Compiler*>(compilerPtr);

	if (slangSourceCode == nullptr)
	{
		return errorResult("Slang source code is not defined.");
	}

	ris_shader_toolkit::GlslProfile glslProfile = static_cast<ris_shader_toolkit::GlslProfile>(profile);
	ris_shader_toolkit::ShaderStage stage = static_cast<ris_shader_toolkit::ShaderStage>(shaderStage);

	// Use "main" as default entry point if none is provided
	std::string entryPoint = (entryPointPtr != nullptr) ? std::string(entryPointPtr) : "main";
	ris_shader_toolkit::ReplaceStageInputNameRule* inputRule = c_to_cpp_ReplaceStageInputNameRule(inputRulePtr);
	ris_shader_toolkit::ReplaceStageOutputNameRule* outputRule = c_to_cpp_ReplaceStageOutputNameRule(outputRulePtr);

	ris_shader_toolkit::CompileResult result = compiler->compileSlangSourceCodeToGlsl(
		std::string(slangSourceCode),
		glslProfile, stage,
		std::string(entryPoint),
		inputRule, outputRule
	);

	delete inputRule;
	delete outputRule;

	return c_to_cpp_CompileResult(result);
}

void* compile_slang_to_wgsl(
	void* compilerPtr,
	const char* inputFilePath,
	int32_t* shaderStages,
	uint32_t shaderStagesCount,
	const char** entryPoints,
	uint32_t entryPointsCount
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

	std::vector<ris_shader_toolkit::ShaderStage> stages;
	for (uint32_t i = 0; i < shaderStagesCount; ++i)
	{
		stages.push_back(static_cast<ris_shader_toolkit::ShaderStage>(shaderStages[i]));
	}

	std::vector<std::string> entryPointNames;
	for (uint32_t i = 0; i < entryPointsCount; ++i)
	{
		entryPointNames.push_back(std::string(entryPoints[i]));
	}

	ris_shader_toolkit::CompileResult result = compiler->compileSlangToWgsl(
		std::string(inputFilePath), stages, entryPointNames);

	return c_to_cpp_CompileResult(result);
}


void* compile_slang_source_code_to_wgsl(
	void* compilerPtr,
	const char* slangSourceCode,
	int32_t* shaderStages,
	uint32_t shaderStagesCount,
	const char** entryPoints,
	uint32_t entryPointsCount
)
{
	if (compilerPtr == nullptr)
	{
		return errorResult("Compiler instance is null.");
	}

	ris_shader_toolkit::Compiler* compiler = static_cast<ris_shader_toolkit::Compiler*>(compilerPtr);

	if (slangSourceCode == nullptr)
	{
		return errorResult("Slang source code cannot be null pointer.");
	}

	std::vector<ris_shader_toolkit::ShaderStage> stages;
	for (uint32_t i = 0; i < shaderStagesCount; ++i)
	{
		stages.push_back(static_cast<ris_shader_toolkit::ShaderStage>(shaderStages[i]));
	}

	std::vector<std::string> entryPointNames;
	for (uint32_t i = 0; i < entryPointsCount; ++i)
	{
		entryPointNames.push_back(std::string(entryPoints[i]));
	}

	ris_shader_toolkit::CompileResult result = compiler->compileSlangSourceCodeToWgsl(
		std::string(slangSourceCode), stages, entryPointNames);

	return c_to_cpp_CompileResult(result);
}

void free_compiler(void* compilerPtr)
{
	ris_shader_toolkit::Compiler* compiler = static_cast<ris_shader_toolkit::Compiler*>(compilerPtr);
	delete compiler;
}


