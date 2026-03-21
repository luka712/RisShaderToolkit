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
bool c_compile_slang_to_glsl_450_vs()
{
	void* compilerPtr = create_compiler();

	c_CompileResult* resultPtr = (c_CompileResult*)compile_slang_to_glsl(
		compilerPtr,
		SOURCE_CODE.c_str(),
		static_cast<int>(ShaderStage::Vertex),
		"main_vs",
		ris_shader_toolkit::GlslProfile::GLSL_450
	);

	bool isSuccess = resultPtr->success;
	std::string sourceCodeStr(resultPtr->sourceCode);
	bool containsMain = sourceCodeStr.find("main") != std::string::npos;

	free_compile_result(resultPtr);
	free_compiler(compilerPtr);

	return isSuccess && containsMain;
}

//! Test if the compiler can successfully compile Slang source code to GLSL 300 es
bool c_compile_slang_to_glsl_300_es_vs()
{
	void* compilerPtr = create_compiler();

	c_CompileResult* resultPtr = (c_CompileResult*)compile_slang_to_glsl(
		compilerPtr,
		SOURCE_CODE.c_str(),
		static_cast<int>(ShaderStage::Vertex),
		nullptr,
		ris_shader_toolkit::GlslProfile::GLES_300
	);

	bool isSuccess = resultPtr->success;
	std::string sourceCodeStr(resultPtr->sourceCode);
	bool containsMain = sourceCodeStr.find("main") != std::string::npos;

	free_compile_result(resultPtr);
	free_compiler(compilerPtr);

	return isSuccess && containsMain;
}

TEST_CASE("c compiler slang to glsl tests", "[c_compile_slang_to_glsl_450_vs, c_compile_slang_to_glsl_300_es_vs]")
{
	REQUIRE(c_compile_slang_to_glsl_450_vs());
	REQUIRE(c_compile_slang_to_glsl_300_es_vs());
}
