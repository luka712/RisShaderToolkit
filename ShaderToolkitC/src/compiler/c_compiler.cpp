#include "compiler/c_compiler.hpp"

void* create_compiler()
{
	return new ris_shader_toolkit::Compiler();
}

char* get_last_error_message()
{
	return lastErrorMessage.empty() ? nullptr : const_cast<char*>(lastErrorMessage.c_str());
}

void* compile_slang_to_wgsl(
	void* compilerPtr,
	const char* sourceCode,
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

	if (sourceCode == nullptr)
	{
		return errorResult("Slang source code is not defined.");
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
		std::string(sourceCode), stages, entryPointNames);

	return c_to_cpp_CompileResult(result);
}

void* compile_slang_to_spirv(
	void* compilerPtr,
	const char* slangSourceCode,
	int32_t shaderStage,
	const char* entryPoint,
	ris_shader_toolkit::SpirVProfile profile)
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

	ris_shader_toolkit::ShaderStage stage = static_cast<ris_shader_toolkit::ShaderStage>(shaderStage);

	std::string entryPointName = "";
	if (entryPoint != nullptr)
	{
		entryPointName = std::string(entryPoint);
	}

	ris_shader_toolkit::CompileResult result = compiler->compileSlangToSpirV(std::string(slangSourceCode), stage, entryPointName, profile);

	return c_to_cpp_CompileResult(result);
}

void* compile_slang_to_glsl(
	void* compilerPtr,
	const char* slangSourceCode,
	int32_t shaderStage,
	const char* entryPoint,
	ris_shader_toolkit::GlslProfile profile
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

	ris_shader_toolkit::ShaderStage stage = static_cast<ris_shader_toolkit::ShaderStage>(shaderStage);

	std::string entryPointName = "";
	if (entryPoint != nullptr)
	{
		entryPointName = std::string(entryPoint);
	}

	ris_shader_toolkit::CompileResult result = compiler->compileSlangToGlsl(std::string(slangSourceCode), stage, entryPointName, profile);

	return c_to_cpp_CompileResult(result);
}

void free_compiler(void* compilerPtr)
{
	ris_shader_toolkit::Compiler* compiler = static_cast<ris_shader_toolkit::Compiler*>(compilerPtr);
	delete compiler;
}


