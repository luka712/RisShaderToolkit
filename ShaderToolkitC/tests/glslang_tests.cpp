#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include "glslang/glslang_compiler.hpp"
#include <iostream>

using namespace shader_toolkit;

bool compile_glsl_to_spirv()
{
    std::string input = "D:/Projects/ShaderToolkitSharp/ShaderToolkitC/test_files/sprite_vs.glsl";

    shader_toolkit::GlslangCompiler compiler;
    shader_toolkit::GlslangCompileResult result = compiler.compile(input, GLSLANG_STAGE_VERTEX);
    std::cout << "SPIR-V Source Code: " << result.getSourceCode() << std::endl;

    return result.isSuccess();
}


TEST_CASE("glslang tests", "[compile_glsl_to_spirv]") {
    REQUIRE(compile_glsl_to_spirv());
}
