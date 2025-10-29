#include "compiler/compiler.hpp"
#include <fstream>
#include <filesystem>

namespace shader_toolkit {
	Compiler::Compiler() : fxcCompiler() {}



	bool Compiler::createFile(
		const std::string& filePath,
		const std::string& content)
	{
		std::ofstream file(filePath);
		if (file.is_open()) {
			file << content;
			file.close();
			return true;
		}

		return false;
	}

	CompileResult Compiler::compileSlangToHlsl(
		const std::string& inputFilePath, 
		ShaderStage shaderStage, 
		HlslProfile profile,
		const std::string& entryPoint)
	{
		// First, compile the Slang shader to HLSL source code using SlangSession
		SlangSession slangSession;
		if (!slangSession.initialize()) {
			return CompileResult::errorResult("Failed to initialize Slang session.");
		}
		SlangCompileResult slangResult = slangSession.compileToHlsl(
			inputFilePath,
			shaderStage,
			entryPoint,
			profile
		);
		if (!slangResult.isSuccess()) {
			return CompileResult::errorResult("Slang compilation failed: " + slangResult.getErrorMessage());
		}
		std::string hlslSourceCode = slangResult.getSourceCode();

		return CompileResult::successResult("", hlslSourceCode);
	}

	CompileResult Compiler::compileSlangToFxc(
		const std::string& inputFilePath,
		const std::string& outputFilePath,
		ShaderStage shaderStage,
		HlslProfile profile,
		const std::string& entryPoint,
		bool columnMajorOrder)
	{
		CompileResult hlslResult = compileSlangToHlsl(inputFilePath, shaderStage, profile, entryPoint);
		if (!hlslResult.isSuccess()) {
			return hlslResult;
		}
		std::string hlslSourceCode = hlslResult.getSourceCode();

		// Create temporary HLSL file
		std::filesystem::path cwd = std::filesystem::current_path();
		std::string tempHlslPath = (cwd / "__temp__.hlsl").string();
		createFile(tempHlslPath, hlslSourceCode);

		// Now, compile the HLSL source code to binary using FxcCompiler
		FxcCompileResult fxcResult = fxcCompiler.compile(
			tempHlslPath,
			outputFilePath,
			shaderStage,
			profile,
			entryPoint
		);
		if (!fxcResult.isSuccess()) {
			return CompileResult::errorResult("FXC compilation failed: " + fxcResult.getErrorMessage());
		}
		return CompileResult::successResult(outputFilePath, "");
	}
}
