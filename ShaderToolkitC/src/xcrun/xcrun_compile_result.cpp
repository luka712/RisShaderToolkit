#include "xcrun/xcrun_compile_result.hpp"


namespace ris_shader_toolkit {

    XcrunCompileResult::XcrunCompileResult(bool success, const std::string& sourceCode, const std::string& error)
        : success(success), sourceCode(sourceCode), errorMessage(error)
    {
    }

    XcrunCompileResult XcrunCompileResult::successResult(const std::string& sourceCode)
    {
        return XcrunCompileResult(true, sourceCode);
    }

    XcrunCompileResult XcrunCompileResult::errorResult(const std::string& errorMessage)
    {
        return XcrunCompileResult(false, "", errorMessage);
    }
}
