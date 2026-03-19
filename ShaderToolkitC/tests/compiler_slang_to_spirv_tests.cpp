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


//! Test if the compiler can successfully compile Slang source code to Spir-V,
//! and if the resulting Spir-V source code contains the expected entry point
//! functions for vertex and fragment shaders. No entry points are explicitly specified,
//! so the compiler should infer them from the Slang source code.
bool compile_slang_to_spir_v()
{
	Compiler compiler;

	auto vertexResult = compiler.compileSlangToSpirV(SOURCE_CODE, ShaderStage::Vertex);
	auto fragmentResult = compiler.compileSlangToSpirV(SOURCE_CODE, ShaderStage::Fragment);

	return vertexResult.isSuccess() && vertexResult.getBinaryCode().size() > 0
		&& fragmentResult.isSuccess() && fragmentResult.getBinaryCode().size() > 0;
}

//! Test if the compiler can successfully compile Slang source code to Spir-V,
//! and if the resulting Spir-V source code contains the expected entry point
//! functions for vertex and fragment shaders. Entry points are explicitly specified.
bool compile_slang_to_spir_v_2()
{
	Compiler compiler;

	auto vertexResult = compiler.compileSlangToSpirV(SOURCE_CODE, ShaderStage::Vertex, "main_vs");
	auto fragmentResult = compiler.compileSlangToSpirV(SOURCE_CODE, ShaderStage::Fragment, "main_fs");

	return vertexResult.isSuccess() && vertexResult.getBinaryCode().size() > 0
		&& fragmentResult.isSuccess() && fragmentResult.getBinaryCode().size() > 0;
}

TEST_CASE("compiler tests", "[compile_slang_to_spir_v, compile_slang_to_spir_v_2]")
{
	REQUIRE(compile_slang_to_spir_v());
	REQUIRE(compile_slang_to_spir_v_2());
}
