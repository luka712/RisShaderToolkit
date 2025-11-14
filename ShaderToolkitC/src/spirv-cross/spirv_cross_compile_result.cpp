#include "spirv-cross/spirv_cross_compile_result.hpp"

namespace ris_shader_toolkit {

    SpirVCrossCompileResult::SpirVCrossCompileResult(bool success, const std::string& sourceCode, const std::string& error)
        : success(success), sourceCode(sourceCode), errorMessage(error)
    {
    }

    SpirVCrossCompileResult SpirVCrossCompileResult::successResult(const std::string& sourceCode)
    {
        return SpirVCrossCompileResult(true, sourceCode);
    }

    SpirVCrossCompileResult SpirVCrossCompileResult::errorResult(const std::string& errorMessage)
    {
        return SpirVCrossCompileResult(false, "", errorMessage);
    }
}
