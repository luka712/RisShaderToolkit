#include "compiler/compile_result.hpp"

namespace shader_toolkit
{
	CompileResult::CompileResult(
		bool success,
		const std::string& outputFilePath,
		const std::string& sourceCode,
		const std::string& error)
		: success(success),
		sourceCode(sourceCode),
		outputFilePath(outputFilePath),
		errorMessage(error)
	{
	}

	CompileResult CompileResult::successResult(
		const std::string& outputFilePath,
		const std::string& sourceCode)
	{
		return CompileResult(true, outputFilePath, sourceCode);
	}

	CompileResult CompileResult::errorResult(
		const std::string& errorMessage)
	{
		return CompileResult(false, "", "", errorMessage);
	}
}