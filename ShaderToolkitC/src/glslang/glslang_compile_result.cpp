#include "glslang/glslang_compile_result.hpp"

namespace shader_toolkit {

    GlslangCompileResult::GlslangCompileResult(bool success, const std::string& sourceCode, const std::string& error)
        : success(success), sourceCode(sourceCode), errorMessage(error)
    {
    }

    GlslangCompileResult GlslangCompileResult::successResult(const std::string& sourceCode)
    {
        return GlslangCompileResult(true, sourceCode);
    }

    GlslangCompileResult GlslangCompileResult::errorResult(const std::string& errorMessage)
    {
        return GlslangCompileResult(false, "", errorMessage);
    }
}
