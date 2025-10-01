
#include "slang/slang_compile_result.hpp"

namespace shader_toolkit {

    SlangCompileResult::SlangCompileResult(bool success, const std::string& sourceCode, const std::string& error)
		: success(success), sourceCode(sourceCode), errorMessage(error)
    {
    }

    SlangCompileResult SlangCompileResult::successResult(const std::string& sourceCode)
    {
        return SlangCompileResult(true, sourceCode);
    }

    SlangCompileResult SlangCompileResult::errorResult(const std::string& errorMessage)
    {
        return SlangCompileResult(false, "", errorMessage);
    }
}
