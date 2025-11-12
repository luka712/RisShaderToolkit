#include <catch2/catch_test_macros.hpp>
#include <compiler/compiler.hpp>

using namespace ris_shader_toolkit;

std::string fxc_vs_output = "D:/Projects/ShaderToolkitSharp/ShaderToolkitC/test_files/sprite_vs.fxc";
std::string fxc_ps_output = "D:/Projects/ShaderToolkitSharp/ShaderToolkitC/test_files/sprite_ps.fxc";

bool compile_slang_vs_to_fxc()
{
	Compiler compiler;
	CompileResult result = compiler.compileSlangToFxc(
		"test_files/sprite.slang",
		fxc_vs_output,
		ShaderStage::Vertex,
		HlslProfile::SM_5_0,
		"main_vs",
		true
	);

	return result.isSuccess();
}

bool compile_slang_ps_to_fxc()
{
	Compiler compiler;
	CompileResult result = compiler.compileSlangToFxc(
		"test_files/sprite.slang",
		fxc_ps_output,
		ShaderStage::Fragment,
		HlslProfile::SM_5_0,
		"main_fs",
		true
	);
	return result.isSuccess();
}


TEST_CASE("compiler tests", "[compile_slang_vs_to_fxc, compile_slang_ps_to_fxc]") {
    REQUIRE(compile_slang_vs_to_fxc());
	REQUIRE(compile_slang_ps_to_fxc());
}