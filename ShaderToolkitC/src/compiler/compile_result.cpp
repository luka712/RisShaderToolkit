#include "compiler/compile_result.hpp"

namespace ris_shader_toolkit
{
	CompileResult::CompileResult(
		bool success,
		const std::string& sourceCode,
		const std::string& error)
		: _success(success),
		_sourceCode(sourceCode),
		_binarySourceCode(),
		_errorMessage(error)
	{
	}

	CompileResult::CompileResult(
		bool success,
		const std::vector<uint8_t>& binaryCode,
		const std::string& error)
		: _success(success),
		_binarySourceCode(binaryCode),
		_sourceCode(""),
		_errorMessage(error)
	{
	}

	CompileResult::CompileResult(
		const std::string& sourceCode,
		ShaderReflection reflection)
		: _success(true),
		_sourceCode(sourceCode),
		_binarySourceCode() {
		_reflectionData = reflection;
	}

	CompileResult::CompileResult(
		const std::vector<uint8_t>& binaryCode,
		ShaderReflection reflection)
		: _success(true),
		_binarySourceCode(binaryCode),
		_sourceCode("") {
		_reflectionData = reflection;
	}

	CompileResult CompileResult::successResult(
		const std::string& sourceCode,
		ShaderReflection reflection
	)
	{
		return CompileResult(sourceCode, reflection);
	}

	CompileResult CompileResult::successResult(
		const std::vector<uint8_t>& binaryCode,
		ShaderReflection reflection
	)
	{
		return CompileResult(binaryCode, reflection);
	}

	CompileResult CompileResult::errorResult(const std::string& errorMessage)
	{
		return CompileResult(false, "", errorMessage);
	}
}