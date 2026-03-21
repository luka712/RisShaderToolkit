#include "compiler/c_compiler.hpp"
#include <spdlog/spdlog.h>

void* create_compiler()
{
	return new ris_shader_toolkit::Compiler();
}

char* get_last_error_message()
{
	return lastErrorMessage.empty() ? nullptr : const_cast<char*>(lastErrorMessage.c_str());
}

#pragma region WGSL

void* compile_slang_to_wgsl(
	void* compilerPtr,
	const char* slangSourceCode,
	int32_t* shaderStages,
	uint32_t shaderStagesCount
) {
	return compile_slang_to_wgsl_ext(compilerPtr, slangSourceCode, shaderStages, shaderStagesCount, nullptr, 0);
}

void* compile_slang_to_wgsl_ext(
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
		std::string message = "Compiler instance is null.";
		spdlog::error(message);
		return errorResult(message.c_str());
	}

	ris_shader_toolkit::Compiler* compiler = static_cast<ris_shader_toolkit::Compiler*>(compilerPtr);

	if (sourceCode == nullptr)
	{
		std::string message = "Slang source code is not defined.";
		spdlog::error(message);
		return errorResult(message.c_str());
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

	spdlog::info("Compiling Slang to WGSL with {} shader stages and {} entry points.", shaderStagesCount, entryPointsCount);

	ris_shader_toolkit::CompileResult result = compiler->compileSlangToWgsl(
		std::string(sourceCode), stages, entryPointNames);

	spdlog::info("Compilation completed. Success: {}. Source code size: {}. Error message size: {}.",
		result.isSuccess(), result.getSourceCode().size(), result.getErrorMessage().size());

	return c_to_cpp_CompileResult(result);
}

#pragma endregion

void* compile_slang_to_spirv(
	void* compilerPtr,
	const char* slangSourceCode,
	int32_t* shaderStages,
	uint32_t shaderStagesCount,
	ris_shader_toolkit::SpirVProfile profile)
{
	return compile_slang_to_spirv_ext(compilerPtr, slangSourceCode, shaderStages, shaderStagesCount, nullptr, 0, profile);
}

void* compile_slang_to_spirv_ext(
	void* compilerPtr,
	const char* slangSourceCode,
	int32_t* shaderStages,
	uint32_t shaderStagesCount,
	const char** entryPoints,
	uint32_t entryPointsCount,
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

	ris_shader_toolkit::CompileResult result = compiler->compileSlangToSpirV(std::string(slangSourceCode), stages, entryPointNames, profile);

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


