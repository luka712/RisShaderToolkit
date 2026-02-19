#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include "slang/slang_session.hpp"
#include <spdlog/spdlog.h>

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


//! Test compilation of Slang to WGSL for vertex shader.
bool create_wgsl_vs_shader_low_level()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}

	SlangCompileResult result = session.compile(
		SOURCE_CODE,
		SLANG_WGSL,
		"",
		{ SLANG_STAGE_VERTEX },
		{ "main_vs" }
	);
	return result.isSuccess() 
		&& result.getSourceCode().find("fn main_vs") != std::string::npos 
		&& result.getSourceCode().find("fn main_fs") == std::string::npos;
}

//! Test compilation of Slang to WGSL for fragment shader.
bool create_wgsl_fs_shader_low_level()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}

	SlangCompileResult result = session.compile(
		SOURCE_CODE,
		SLANG_WGSL,
		"",
		{ SLANG_STAGE_FRAGMENT },
		{ "main_fs" }
	);
	return result.isSuccess()
		&& result.getSourceCode().find("fn main_fs") != std::string::npos
		&& result.getSourceCode().find("fn main_vs") == std::string::npos;
}

//! Test compilation of Slang to WGSL.
bool create_wgsl_shader_low_level()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}

	SlangCompileResult result = session.compile(
		SOURCE_CODE,
		SLANG_WGSL,
		"",
		{ SLANG_STAGE_VERTEX, SLANG_STAGE_FRAGMENT },
		{ "main_vs", "main_fs" }
	);
	return result.isSuccess()
		&& result.getSourceCode().find("fn main_fs") != std::string::npos
		&& result.getSourceCode().find("fn main_vs") != std::string::npos;
}

//! Test compilation of Slang to WGSL using the high-level API.
bool create_wgsl_shader_high_level()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}

	SlangCompileResult result = session.compileToWgsl(
		SOURCE_CODE,
		{ ShaderStage::Vertex , ShaderStage::Fragment },
		{}
	);
	return result.isSuccess()
		&& result.getSourceCode().find("fn main_fs") != std::string::npos
		&& result.getSourceCode().find("fn main_vs") != std::string::npos;
}

const std::string TESTS = R"(
	[create_wgsl_vs_shader_low_level, create_wgsl_fs_shader_low_level, create_wgsl_shader_low_level], 
	[create_wgsl_shader_high_level])";

TEST_CASE("slang tests") {

	SECTION("slang to wgsl low level") {
		spdlog::info("Running test: slang to wgsl low level");
		REQUIRE(create_wgsl_vs_shader_low_level());
		REQUIRE(create_wgsl_fs_shader_low_level());
		REQUIRE(create_wgsl_shader_low_level());
	}
	
	SECTION("slang to wgsl high level") {
		spdlog::info("Running test: slang to wgsl high level");
		// High level
		REQUIRE(create_wgsl_shader_high_level());
	}
}
