#include <catch2/catch_test_macros.hpp>
#include <compiler/compiler.hpp>
#include <iostream>
#include <spirv-cross/spirv_cross_compiler.hpp>

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


//! Test if the compiler can successfully compile Spir-V source code to GLSL 4.5,
bool compile_spirv_to_glsl_450_vs()
{
	Compiler compiler;

	std::vector<ShaderStage> stages = { ShaderStage::Vertex };
	auto spirVResult = compiler.compileSlangToSpirV(
		SOURCE_CODE,
		stages
	);

	SpirVCrossCompiler crossCompiler;
	auto glslResult = crossCompiler.compile(spirVResult.getBinaryCode(), GlslProfile::GLSL_450, ShaderStage::Vertex);

	return glslResult.isSuccess() && glslResult.getSourceCode().find("main") != std::string::npos;
}

//! Test if the compiler can successfully compile Spir-V source code to GLSL 4.5,
bool compile_spirv_to_glsl_450_fs()
{
	Compiler compiler;

	std::vector<ShaderStage> stages = { ShaderStage::Fragment };
	auto spirVResult = compiler.compileSlangToSpirV(
		SOURCE_CODE,
		stages
	);

	SpirVCrossCompiler crossCompiler;
	auto glslResult = crossCompiler.compile(spirVResult.getBinaryCode(), GlslProfile::GLSL_450, ShaderStage::Fragment);

	return glslResult.isSuccess() && glslResult.getSourceCode().find("main") != std::string::npos;
}

//! Test if the compiler can successfully compile Spir-V source code to GLSL 300 es
bool compile_spirv_to_glsl_300_es_vs()
{
	Compiler compiler;

	std::vector<ShaderStage> stages = { ShaderStage::Vertex };
	std::vector<std::string> entryPoints = { "main_vs" };
	auto spirVResult = compiler.compileSlangToSpirV(
		SOURCE_CODE,
		stages,
		entryPoints
	);

	SpirVCrossCompiler crossCompiler;
	auto glslResult = crossCompiler.compile(spirVResult.getBinaryCode(), GlslProfile::GLES_300, ShaderStage::Vertex);

	return glslResult.isSuccess() && glslResult.getSourceCode().find("main") != std::string::npos;
}

bool compile_spirv_to_glsl_300_es_fs()
{
	Compiler compiler;

	std::vector<ShaderStage> stages = { ShaderStage::Fragment };
	std::vector<std::string> entryPoints = { "main_fs" };
	auto spirVResult = compiler.compileSlangToSpirV(
		SOURCE_CODE,
		stages,
		entryPoints
	);

	SpirVCrossCompiler crossCompiler;
	auto glslResult = crossCompiler.compile(spirVResult.getBinaryCode(), GlslProfile::GLES_300, ShaderStage::Fragment);

	return glslResult.isSuccess() && glslResult.getSourceCode().find("main") != std::string::npos;
}

TEST_CASE("compiler spirv to glsl tests",
	"[compile_spirv_to_glsl_450_vs, compile_spirv_to_glsl_450_fs, compile_spirv_to_glsl_300_es_vs,compile_spirv_to_glsl_300_es_fs ]")
{
	REQUIRE(compile_spirv_to_glsl_450_vs());
	REQUIRE(compile_spirv_to_glsl_450_fs());
	REQUIRE(compile_spirv_to_glsl_300_es_vs());
	REQUIRE(compile_spirv_to_glsl_300_es_fs());
}
