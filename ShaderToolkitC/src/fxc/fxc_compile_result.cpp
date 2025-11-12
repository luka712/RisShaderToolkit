#include "fxc/fxc_compile_result.hpp"

namespace ris_shader_toolkit {

    FxcCompileResult::FxcCompileResult(bool success, const std::string& sourceCode, const std::string& error)
        : success(success), sourceCode(sourceCode), errorMessage(error)
    {
    }

    FxcCompileResult FxcCompileResult::successResult(const std::string& sourceCode)
    {
        return FxcCompileResult(true, sourceCode);
    }

    FxcCompileResult FxcCompileResult::errorResult(const std::string& errorMessage)
    {
        return FxcCompileResult(false, "", errorMessage);
    }
}
