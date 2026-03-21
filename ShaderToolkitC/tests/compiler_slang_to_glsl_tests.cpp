#include <catch2/catch_test_macros.hpp>
#include <compiler/compiler.hpp>
#include <iostream>

using namespace ris_shader_toolkit;


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


//! Test if the compiler can successfully compile Slang source code to GLSL 4.5,
bool compile_slang_to_glsl_450()
{
	Compiler compiler;

	CompileResult vertexResult = compiler.compileSlangToGlsl(
		SOURCE_CODE,
		ShaderStage::Vertex,
		"main_vs",
		GlslProfile::GLSL_450
	);

	CompileResult fragmentResult = compiler.compileSlangToGlsl(
		SOURCE_CODE,
		ShaderStage::Fragment,
		"main_fs",
		GlslProfile::GLSL_450
	);

	return vertexResult.isSuccess() && vertexResult.getSourceCode().find("main") != std::string::npos
		&& fragmentResult.isSuccess() && fragmentResult.getSourceCode().find("main") != std::string::npos;
}

//! Test if the compiler can successfully compile Slang source code to GLSL 300 es
bool compile_slang_to_glsl_300_es()
{
	Compiler compiler;

	CompileResult vertexResult = compiler.compileSlangToGlsl(
		SOURCE_CODE,
		ShaderStage::Vertex,
		"",
		GlslProfile::GLES_300
	);

	CompileResult fragmentResult = compiler.compileSlangToGlsl(
		SOURCE_CODE,
		ShaderStage::Fragment,
		"",
		GlslProfile::GLES_300
	);

	return vertexResult.isSuccess() && vertexResult.getSourceCode().find("main") != std::string::npos
		&& fragmentResult.isSuccess() && fragmentResult.getSourceCode().find("main") != std::string::npos;
}

TEST_CASE("compiler slang to glsl tests", "[compile_slang_to_glsl_450, compile_slang_to_glsl_300_es]")
{
	REQUIRE(compile_slang_to_glsl_450());
	REQUIRE(compile_slang_to_glsl_300_es());
}
