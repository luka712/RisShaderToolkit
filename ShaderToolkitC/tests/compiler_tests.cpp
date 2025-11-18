#include <catch2/catch_test_macros.hpp>
#include <compiler/compiler.hpp>
#include <iostream>

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

bool compile_slang_to_glsl_es()
{
	Compiler compiler;
	CompileResult result = compiler.compileSlangToGlsl(
		"test_files/sprite.slang",
		GlslProfile::GLES_300,
		ShaderStage::Vertex,
		"main_vs"
	);
	return result.isSuccess();
}

bool compile_slang_to_glsl_es_formatted()
{
	Compiler compiler;
	
	ReplaceStageInputNameRule vertexInputRule;
	vertexInputRule.setPrefix("v_");

	ReplaceStageOutputNameRule vertexOutputRule;
	vertexOutputRule.setPrefix("f_");
	vertexOutputRule.setTrimEntryPointName(true);

	CompileResult result = compiler.compileSlangToGlsl(
		"test_files/sprite.slang",
		GlslProfile::GLES_300,
		ShaderStage::Vertex,
		"main_vs",
		&vertexInputRule,
		&vertexOutputRule
	);

	if(!result.isSuccess()) {
		std::cout << "Error: " << result.getErrorMessage() << std::endl;
		return false;
	}

	// Now do the fragment shader as well
	ReplaceStageInputNameRule fragmentInputRule;
	fragmentInputRule.setPrefix("f_");

	ReplaceStageOutputNameRule fragmentOutputRule;
	fragmentOutputRule.setPrefix("o_");
	fragmentOutputRule.setTrimEntryPointName(true);

	result = compiler.compileSlangToGlsl(
		"test_files/sprite.slang",
		GlslProfile::GLES_300,
		ShaderStage::Fragment,
		"main_fs",
		&fragmentInputRule,
		&fragmentOutputRule
	);

	return result.isSuccess();
}


TEST_CASE("compiler tests", "[compile_slang_vs_to_fxc, compile_slang_ps_to_fxc, \
	compile_slang_to_glsl_es, compile_slang_to_glsl_es_formatted]") {
    REQUIRE(compile_slang_vs_to_fxc());
	REQUIRE(compile_slang_ps_to_fxc());
	REQUIRE(compile_slang_to_glsl_es());
	REQUIRE(compile_slang_to_glsl_es_formatted());
}