
#include "slang/slang_compile_result.hpp"

namespace ris_shader_toolkit {

    SlangCompileResult::SlangCompileResult(bool success, const std::string& sourceCode, ShaderReflection shaderReflection, const std::string& error)
		: _success(success), _sourceCode(sourceCode), _errorMessage(error), _binaryCode()
    {
		_reflectionData = shaderReflection;
    }

    SlangCompileResult::SlangCompileResult(bool success, const std::vector<uint32_t>& binaryCode, ShaderReflection shaderReflection, const std::string& error)
		: _success(success), _binaryCode(binaryCode), _errorMessage(error), _sourceCode("")
    {
        _reflectionData = shaderReflection;
    }

    SlangCompileResult SlangCompileResult::successResult(const std::string& sourceCode, ShaderReflection shaderReflection)
    {
        return SlangCompileResult(true, sourceCode, shaderReflection);
    }

    SlangCompileResult SlangCompileResult::successResult(const std::vector<uint32_t>& binaryCode, ShaderReflection shaderReflection)
    {
        return SlangCompileResult(true, binaryCode, shaderReflection);
    }

    SlangCompileResult SlangCompileResult::errorResult(const std::string& errorMessage)
    {
        return SlangCompileResult(false, "", ShaderReflection(), errorMessage);
    }
}
