#include "compiler/compile_result.hpp"

namespace ris_shader_toolkit
{
	CompileResult::CompileResult(
		bool success,
		const std::string& outputFilePath,
		const std::string& sourceCode,
		const std::string& error)
		: _success(success),
		_sourceCode(sourceCode),
		_outputFilePath(outputFilePath),
		_errorMessage(error)
	{
	}

	CompileResult::CompileResult(
		const std::string& outputFilePath,
		const std::string& sourceCode,
		ShaderReflection reflection)
		: _success(true),
		_sourceCode(sourceCode),
		_outputFilePath(outputFilePath) {
		_reflectionData = reflection;
	}

	CompileResult CompileResult::successResult(
		const std::string& outputFilePath,
		const std::string& sourceCode,
		ShaderReflection reflection
	)
	{
		return CompileResult(outputFilePath, sourceCode, reflection);
	}

	CompileResult CompileResult::errorResult(
		const std::string& errorMessage)
	{
		return CompileResult(false, "", "", errorMessage);
	}
}