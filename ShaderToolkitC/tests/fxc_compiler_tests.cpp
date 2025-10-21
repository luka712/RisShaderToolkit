#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include "fxc/fxc_compiler.hpp"
#include <iostream>

using namespace shader_toolkit;

bool compile_hlsl_to_fxc()
{
#if _WIN32
    std::string input = "D:/Projects/ShaderToolkitSharp/ShaderToolkitC/test_files/sprite_vs.hlsl";
    std::string output = "D:/Projects/ShaderToolkitSharp/ShaderToolkitC/test_files/sprite_vs_fxc.cso";

    shader_toolkit::FxcCompiler fxcCompiler;
    shader_toolkit::FxcCompileResult result = fxcCompiler.compile(input, output);
    std::cout << "FXC Source Code: " << result.getSourceCode() << std::endl;

    return result.isSuccess();
#else
    return true; // We only need to test on windows
#endif
}


TEST_CASE("fxc tests", "[compile_hlsl_to_fxc]") {
    REQUIRE(compile_hlsl_to_fxc());
}
