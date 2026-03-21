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


//! Test if the compiler can successfully compile Slang source code to WGSL, 
//! and if the resulting WGSL source code contains the expected entry point 
//! functions for vertex and fragment shaders. No entry points are explicitly specified,
//! so the compiler should infer them from the Slang source code.
bool compile_slang_to_wgsl()
{
	Compiler compiler;

	std::vector<ShaderStage> stages = { ShaderStage::Vertex, ShaderStage::Fragment };
	std::vector<std::string> entryPoints; 
	CompileResult result = compiler.compileSlangToWgsl(SOURCE_CODE,stages,entryPoints);

	return result.isSuccess() && result.getSourceCode().find("fn main_vs") != std::string::npos && result.getSourceCode().find("fn main_fs") != std::string::npos;
}

//! Test if the compiler can successfully compile Slang source code to WGSL, 
//! and if the resulting WGSL source code contains the expected entry point 
//! functions for vertex and fragment shaders. Entry points are explicitly specified.
bool compile_slang_to_wgsl_2()
{
	Compiler compiler;

	std::vector<ShaderStage> stages = { ShaderStage::Vertex, ShaderStage::Fragment };
	std::vector<std::string> entryPoints = { "main_vs", "main_fs" };
	CompileResult result = compiler.compileSlangToWgsl(SOURCE_CODE, stages, entryPoints);

	return result.isSuccess() && result.getSourceCode().find("fn main_vs") != std::string::npos && result.getSourceCode().find("fn main_fs") != std::string::npos;
}

TEST_CASE("compiler tests", "[compile_slang_to_wgsl, compile_slang_to_wgsl_2]")
{
	REQUIRE(compile_slang_to_wgsl());
	REQUIRE(compile_slang_to_wgsl_2());
}