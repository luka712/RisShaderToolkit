#include "compiler/compiler.hpp"
#include "util/binary_util.hpp"
#include <fstream>
#include <filesystem>
#include <spirv-cross/spirv_cross_compiler.hpp>
#include <spdlog/spdlog.h>

namespace ris_shader_toolkit {
	Compiler::Compiler() : _fxcCompiler() {
	}

	//bool Compiler::createFile(
	//	const std::string& filePath,
	//	const std::string& content)
	//{
	//	std::ofstream file(filePath);
	//	if (file.is_open()) {
	//		file << content;
	//		file.close();
	//		return true;
	//	}

	//	return false;
	//}

//
//	CompileResult Compiler::compileSlangToHlsl(
//		const std::string& inputFilePath,
//		ShaderStage shaderStage,
//		HlslProfile profile,
//		const std::string& entryPoint)
//	{
//		// First, compile the Slang shader to HLSL source code using SlangSession
//		SlangSession slangSession;
//		if (!slangSession.initialize()) {
//			return CompileResult::errorResult("Failed to initialize Slang session.");
//		}
//		SlangCompileResult slangResult = slangSession.compileToHlsl(
//			inputFilePath,
//			shaderStage,
//			entryPoint,
//			profile
//		);
//		if (!slangResult.isSuccess()) {
//			return CompileResult::errorResult("Slang compilation failed: " + slangResult.getErrorMessage());
//		}
//		std::string hlslSourceCode = slangResult.getSourceCode();
//
//		return CompileResult::successResult("", hlslSourceCode, ShaderReflection());
//	}
//
//	CompileResult Compiler::compileSlangToFxc(
//		const std::string& inputFilePath,
//		const std::string& outputFilePath,
//		ShaderStage shaderStage,
//		HlslProfile profile,
//		const std::string& entryPoint,
//		bool columnMajorOrder)
//	{
//		CompileResult hlslResult = compileSlangToHlsl(inputFilePath, shaderStage, profile, entryPoint);
//		if (!hlslResult.isSuccess()) {
//			return hlslResult;
//		}
//		std::string hlslSourceCode = hlslResult.getSourceCode();
//
//		// Create temporary HLSL file
//		std::filesystem::path cwd = std::filesystem::current_path();
//		std::string tempHlslPath = (cwd / "__temp__.hlsl").string();
//		createFile(tempHlslPath, hlslSourceCode);
//
//		// Now, compile the HLSL source code to binary using FxcCompiler
//		FxcCompileResult fxcResult = _fxcCompiler.compile(
//			tempHlslPath,
//			outputFilePath,
//			shaderStage,
//			profile,
//			entryPoint
//		);
//		if (!fxcResult.isSuccess()) {
//			return CompileResult::errorResult("FXC compilation failed: " + fxcResult.getErrorMessage());
//		}
//		return CompileResult::successResult(outputFilePath, "", ShaderReflection());
//	}
//
//	CompileResult Compiler::compileSlangSourceCodeToGlsl(
//		const std::string& slangSourceCode,
//		GlslProfile profile,
//		ShaderStage shaderStage,
//		const std::string& entryPoint,
//		ReplaceStageInputNameRule* replaceStageInputNameRule,
//		ReplaceStageOutputNameRule* replaceStageOutputNameRule
//	)
//	{
//		spdlog::info("Compiling Slang shader to GLSL: {}", slangSourceCode);
//		// First we need to determine if we can use Slang directly to GLSL or if we need to go through SPIR-V
//
//		// For GLES profiles, we need to go through SPIR-V
//		if (profile == GlslProfile::GLES_300
//			|| profile == GlslProfile::GLES_310
//			|| profile == GlslProfile::GLES_320
//			) {
//			CompileResult spirvResult = compileSlangSourceCodeToSpirV(
//				slangSourceCode,
//				shaderStage,
//				SpirVProfile::SPIRV_1_5,
//				entryPoint
//			);
//			if (!spirvResult.isSuccess()) {
//				return spirvResult;
//			}
//
//			// Convert SPIR-V to GLSL using SpirVCrossCompiler
//			std::vector<uint32_t> spirvBinary = stringToBinary<uint32_t>(spirvResult.getSourceCode());
//			SpirVCrossCompiler spirvCompiler;
//			SpirVCrossCompileResult glslResult = spirvCompiler.compile(
//				spirvBinary,
//				profile,
//				replaceStageInputNameRule,
//				replaceStageOutputNameRule
//			);
//			if (!glslResult.isSuccess()) {
//				return CompileResult::errorResult("SPIR-V to GLSL compilation failed: " + glslResult.getErrorMessage());
//			}
//
//			return CompileResult::successResult("", glslResult.getSourceCode(), ShaderReflection());
//		}
//
//		SlangSession slangSession;
//		if (!slangSession.initialize()) {
//			return CompileResult::errorResult("Failed to initialize Slang session.");
//		}
//
//		SlangCompileResult slangResult = slangSession.compileSourceCodeToGlsl(
//			slangSourceCode,
//			shaderStage,
//			entryPoint,
//			profile
//		);
//		if (!slangResult.isSuccess()) {
//			return CompileResult::errorResult("Slang compilation to GLSL failed: " + slangResult.getErrorMessage());
//		}
//		std::string glslSourceCode = slangResult.getSourceCode();
//		return CompileResult::successResult("", glslSourceCode, ShaderReflection());
//	}
//
//
//	CompileResult Compiler::compileSlangToGlsl(
//		const std::string& inputFilePath,
//		GlslProfile profile,
//		ShaderStage shaderStage,
//		const std::string& entryPoint,
//		ReplaceStageInputNameRule* replaceStageInputNameRule,
//		ReplaceStageOutputNameRule* replaceStageOutputNameRule
//	)
//	{
//		spdlog::info("Compiling Slang shader to GLSL: {}", inputFilePath);
//		// First we need to determine if we can use Slang directly to GLSL or if we need to go through SPIR-V
//
//		// For GLES profiles, we need to go through SPIR-V
//		if (profile == GlslProfile::GLES_300
//			|| profile == GlslProfile::GLES_310
//			|| profile == GlslProfile::GLES_320
//			) {
//			spdlog::info("Need to compile via SPIR-V for GLES profile first.");
//			CompileResult spirvResult = compileSlangToSpirV(
//				inputFilePath,
//				shaderStage,
//				SpirVProfile::SPIRV_1_5,
//				entryPoint
//			);
//			if (!spirvResult.isSuccess()) {
//				return spirvResult;
//			}
//
//			// Convert SPIR-V to GLSL using SpirVCrossCompiler
//			std::vector<uint32_t> spirvBinary = stringToBinary<uint32_t>(spirvResult.getSourceCode());
//			SpirVCrossCompiler spirvCompiler;
//			SpirVCrossCompileResult glslResult = spirvCompiler.compile(
//				spirvBinary,
//				profile,
//				replaceStageInputNameRule,
//				replaceStageOutputNameRule
//			);
//			if (!glslResult.isSuccess()) {
//				return CompileResult::errorResult("SPIR-V to GLSL compilation failed: " + glslResult.getErrorMessage());
//			}
//
//			spdlog::info("Successfully compiled Slang shader to GLSL via SPIR-V.");
//			return CompileResult::successResult("", glslResult.getSourceCode(), ShaderReflection());
//		}
//
//		SlangSession slangSession;
//		if (!slangSession.initialize()) {
//			return CompileResult::errorResult("Failed to initialize Slang session.");
//		}
//
//		SlangCompileResult slangResult = slangSession.compileToGlsl(
//			inputFilePath,
//			shaderStage,
//			entryPoint,
//			profile
//		);
//		if (!slangResult.isSuccess()) {
//			return CompileResult::errorResult("Slang compilation to GLSL failed: " + slangResult.getErrorMessage());
//		}
//		std::string glslSourceCode = slangResult.getSourceCode();
//		return CompileResult::successResult("", glslSourceCode, ShaderReflection());
//	}
//
	CompileResult Compiler::compileSlangToSpirV(
		const std::string& sourceCode,
		std::vector<ShaderStage> shaderStages,
		std::vector<std::string> entryPoints,
		SpirVProfile profile
	)
	{
		SlangSession slangSession;
		if (!slangSession.initialize()) {
			std::string errorMsg = "Failed to initialize Slang session.";
			spdlog::error(errorMsg);
			return CompileResult::errorResult(errorMsg);
		}

		SlangCompileResult slangResult = slangSession.compileToSpirV(
			sourceCode,
			shaderStages,
			entryPoints,
			profile
		);
		if (!slangResult.isSuccess()) {
			std::string errorMsg = "Slang compilation failed: " + slangResult.getErrorMessage();
			spdlog::error(errorMsg);
			return CompileResult::errorResult(errorMsg);
		}
		auto& spirvCode = slangResult.getBinaryCode();
		return CompileResult::successResult(spirvCode, ShaderReflection());
	}

	CompileResult Compiler::compileSlangToWgsl(
		const std::string& sourceCode,
		std::vector<ShaderStage> shaderStages,
		std::vector<std::string> entryPoints
	)
	{
		SlangSession slangSession;
		if (!slangSession.initialize()) {
			return CompileResult::errorResult("Failed to initialize Slang session.");
		}

		SlangCompileResult slangResult = slangSession.compileToWgsl(sourceCode, shaderStages, entryPoints);
		if (!slangResult.isSuccess()) {
			return CompileResult::errorResult("Slang compilation to WGSL failed: " + slangResult.getErrorMessage());
		}
		std::string glslSourceCode = slangResult.getSourceCode();
		return CompileResult::successResult(glslSourceCode, ShaderReflection());
	}

	CompileResult Compiler::compileSlangToWgsl(
		const std::string& sourceCode,
		std::vector<ShaderStage> shaderStages)
	{
		return compileSlangToWgsl(sourceCode, shaderStages, {});
	}
}
