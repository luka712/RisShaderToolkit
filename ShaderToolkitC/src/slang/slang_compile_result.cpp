
#include "slang/slang_compile_result.hpp"

namespace ris_shader_toolkit {

    SlangCompileResult::SlangCompileResult(bool success, const std::string& sourceCode, ShaderReflection shaderReflection, const std::string& error)
		: _success(success), _sourceCode(sourceCode), _errorMessage(error)
    {
		_reflectionData = shaderReflection;
    }

    SlangCompileResult SlangCompileResult::successResult(const std::string& sourceCode, ShaderReflection shaderReflection)
    {
        return SlangCompileResult(true, sourceCode, shaderReflection);
    }

    SlangCompileResult SlangCompileResult::errorResult(const std::string& errorMessage)
    {
        return SlangCompileResult(false, "", ShaderReflection(), errorMessage);
    }
}
