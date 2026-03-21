#include <catch2/catch_test_macros.hpp>
#include <compiler/c_compiler.hpp>
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
bool c_compile_slang_to_wgsl()
{
	void* compilerPtr = create_compiler();

	int32_t shaderStages[] = { static_cast<int32_t>(ShaderStage::Vertex), static_cast<int32_t>(ShaderStage::Fragment) };

	c_CompileResult* resultPtr = (c_CompileResult*)compile_slang_to_wgsl(
		compilerPtr,
		SOURCE_CODE.c_str(),
		shaderStages,
		2
	);

	bool isSuccess = resultPtr->success;

	free_compile_result(resultPtr);
	free_compiler(compilerPtr);

	return isSuccess;
}

bool c_compile_slang_to_wgsl_with_entry_points()
{
	void* compilerPtr = create_compiler();
	int32_t shaderStages[] = { static_cast<int32_t>(ShaderStage::Vertex), static_cast<int32_t>(ShaderStage::Fragment) };
	const char* entryPoints[] = { "main_vs", "main_fs" };
	c_CompileResult* resultPtr = (c_CompileResult*)compile_slang_to_wgsl_ext(
		compilerPtr,
		SOURCE_CODE.c_str(),
		shaderStages,
		2,
		entryPoints,
		2
	);
	bool isSuccess = resultPtr->success;
	free_compile_result(resultPtr);
	free_compiler(compilerPtr);
	return isSuccess;
}

TEST_CASE("c compiler slang to glsl tests", "[c_compile_slang_to_wgsl, c_compile_slang_to_wgsl_with_entry_points]")
{
	REQUIRE(c_compile_slang_to_wgsl());
	REQUIRE(c_compile_slang_to_wgsl_with_entry_points());
}
