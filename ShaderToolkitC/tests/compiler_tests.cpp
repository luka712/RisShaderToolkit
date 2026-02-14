#include <catch2/catch_test_macros.hpp>
#include <compiler/compiler.hpp>
#include <iostream>

using namespace ris_shader_toolkit;

std::string fxc_vs_output = "D:/Projects/ShaderToolkitSharp/ShaderToolkitC/test_files/sprite_vs.fxc";
std::string fxc_ps_output = "D:/Projects/ShaderToolkitSharp/ShaderToolkitC/test_files/sprite_ps.fxc";


const std::string SOURCE_CODE = R"(struct VSInput
{ 
	float3 position : POSITION;
	float2 texCoord : TEXCOORD0;
	float4 color : COLOR0;
}

struct VSOutput
{
	float4 position : SV_POSITION;
	float2 texCoord : TEXCOORD0;
	float4 color : COLOR0;
}

ConstantBuffer<float4x4> viewProjection : register(b0, space0);

[shader("vertex")]
VSOutput main_vs(VSInput input)
{
	VSOutput output;
	output.position = mul(viewProjection, float4(input.position, 1.0));
	output.texCoord = input.texCoord;
	output.color = input.color;
	return output;
}

Texture2D diffuseTexture: register(t0, space1);
SamplerState diffuseTexSampler : register(s1, space1);

[shader("fragment")]
float4 main_fs(VSOutput input) : SV_TARGET
{
	float4 textureColor = diffuseTexture.Sample(diffuseTexSampler, input.texCoord);
	return textureColor * input.color;
})";

bool compile_slang_vs_to_fxc()
{
#if _WIN32
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
#else
	return true;
#endif
}

bool compile_slang_ps_to_fxc()
{
#if _WIN32
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
#else
	return true;
#endif
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

bool compile_slang_to_wgsl_formatted()
{
	Compiler compiler;

	ReplaceStageInputNameRule vertexInputRule;

	ReplaceStageOutputNameRule vertexOutputRule;
	vertexOutputRule.setPrefix("f_");
	vertexOutputRule.setTrimEntryPointName(true);

	CompileResult result = compiler.compileSlangSourceCodeToWgsl(
		"test_files/sprite.slang",
		ShaderStage::Vertex,
		"main_vs",
		&vertexInputRule,
		&vertexOutputRule
	);

	if (!result.isSuccess()) {
		std::cout << "Error: " << result.getErrorMessage() << std::endl;
		return false;
	}

	// Now do the fragment shader as well
	ReplaceStageInputNameRule fragmentInputRule;
	fragmentInputRule.setPrefix("f_");

	ReplaceStageOutputNameRule fragmentOutputRule;
	fragmentOutputRule.setPrefix("o_");
	fragmentOutputRule.setTrimEntryPointName(true);

	result = compiler.compileSlangToWgsl(
		"test_files/sprite.slang",
		ShaderStage::Fragment,
		"main_fs",
		&fragmentInputRule,
		&fragmentOutputRule
	);

	return result.isSuccess();
}

bool compile_slang_source_code_to_wgsl()
{
	Compiler compiler;

	CompileResult result = compiler.compileSlangSourceCodeToWgsl(
		"test_files/sprite.slang",
		{ ShaderStage::Vertex, ShaderStage::Fragment },
		{ }
	);

	return result.isSuccess();
}

TEST_CASE("compiler tests", "[compile_slang_vs_to_fxc, compile_slang_ps_to_fxc, \
	compile_slang_to_glsl_es, compile_slang_to_glsl_es_formatted] \
	[compile_slang_to_wgsl_formatted, compile_slang_source_code_to_wgsl]") {
    REQUIRE(compile_slang_vs_to_fxc());
	REQUIRE(compile_slang_ps_to_fxc());
	REQUIRE(compile_slang_to_glsl_es());
	REQUIRE(compile_slang_to_glsl_es_formatted());
	REQUIRE(compile_slang_to_wgsl_formatted());
	REQUIRE(compile_slang_source_code_to_wgsl());
}