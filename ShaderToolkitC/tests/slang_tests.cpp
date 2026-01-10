#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include "slang/slang_session.hpp"

using namespace ris_shader_toolkit;

bool create_slang_session()
{
	ris_shader_toolkit::SlangSession session;
	return session.initialize();
}

bool create_hlsl_shader_low_level()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}

	SlangCompileResult result = session.compile(
		"test_files/sprite.slang",
		SLANG_HLSL,
		"sm_5_0",
		SLANG_STAGE_VERTEX,
		"main_vs"
	);
	return result.isSuccess();
}

bool create_hlsl_shader_high_level()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}
	SlangCompileResult result = session.compileToHlsl(
		"test_files/sprite.slang",
		ShaderStage::Vertex,
		"main_vs",
		HlslProfile::SM_5_0
	);
	return result.isSuccess();
}

bool create_glsl_shader_low_level()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}

	SlangCompileResult result = session.compile(
		"test_files/sprite.slang",
		SLANG_GLSL,
		"glsl_450",
		SLANG_STAGE_VERTEX,
		"main_vs"
	);
	return result.isSuccess();
}

bool create_glsl_shader_high_level()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}
	SlangCompileResult result = session.compileToGlsl(
		"test_files/sprite.slang",
		ShaderStage::Vertex,
		"main_vs",
		GlslProfile::GLSL_440
	);
	return result.isSuccess();
}

bool create_metal_shader_low_level()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}

	SlangCompileResult result = session.compile(
		"test_files/sprite.slang",
		SLANG_METAL,
		"metallib_2_3",
		SLANG_STAGE_VERTEX,
		"main_vs"
	);
	return result.isSuccess();
}

bool create_metal_shader_high_level()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}
	SlangCompileResult result = session.compileToMetal(
		"test_files/sprite.slang",
		ShaderStage::Vertex,
		"main_vs",
		MetalProfile::MSL_2_3
	);
	return result.isSuccess();
}

bool create_metal_shader_low_level_multistage()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}

	SlangCompileResult result = session.compile(
		"test_files/sprite.slang",
		SLANG_METAL,
		"metallib_2_3",
		{ SLANG_STAGE_VERTEX, SLANG_STAGE_FRAGMENT },
		{ "main_vs", "main_fs" }
	);
	return result.isSuccess();
}

bool create_metal_shader_high_level_multistage()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}
	SlangCompileResult result = session.compileToMetal(
		"test_files/sprite.slang",
		{ ShaderStage::Vertex, ShaderStage::Fragment },
		{ "main_vs", "main_fs" },
		MetalProfile::MSL_2_3
	);
	return result.isSuccess();
}

bool create_spirv_shader_low_level()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}
	SlangCompileResult result = session.compile(
		"test_files/sprite.slang",
		SLANG_SPIRV,
		"spirv_1_5",
		SLANG_STAGE_VERTEX,
		"main_vs"
	);
	return result.isSuccess();
}

bool create_spirv_shader_multistage()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}
	SlangCompileResult result = session.compileToSpirV(
		"test_files/sprite.slang",
		{ ShaderStage::Vertex, ShaderStage::Fragment },
		{ "main_vs", "main_fs" },
		SpirVProfile::SPIRV_1_5
	);
	return result.isSuccess();
}

bool create_glsl_from_source_code()
{
	ris_shader_toolkit::SlangSession session;
	if (!session.initialize())
	{
		return false;
	}

	const char* sourceCode = R"(
struct VSOut {
    float4 position : SV_Position;
};

VSOut main(uint vertexID : SV_VertexID) {
    // Fullscreen triangle
    float2 pos = float2(
        (vertexID == 2) ? 3.0 : -1.0,
        (vertexID == 1) ? 3.0 : -1.0
    );

    VSOut o;
    o.position = float4(pos, 0.0, 1.0);
    return o;
}
)";



	SlangCompileResult result = session.compileFromSourceCode(
		sourceCode,
		SLANG_GLSL,
		"glsl_450",
		SLANG_STAGE_VERTEX,
		"main");
	return result.isSuccess();
}

TEST_CASE("slang tests", "[create_slang_session],\
 [create_hlsl_shader_low_level], [create_hlsl_shader_high_level], \
 [create_glsl_shader_low_level], [create_glsl_shader_high_level], [create_glsl_es_shader_low_level], [create_glsl_from_source_code] \
[create_metal_shader_low_level], [create_metal_shader_high_level], [create_metal_shader_low_level_multistage], [create_metal_shader_high_level_multistage] \
[create_spirv_shader_low_level], [create_spirv_shader_multistage]"
) {
	REQUIRE(create_slang_session());
	REQUIRE(create_hlsl_shader_low_level());
	REQUIRE(create_hlsl_shader_high_level());
	REQUIRE(create_glsl_shader_low_level());
	REQUIRE(create_glsl_shader_high_level());
	REQUIRE(create_glsl_from_source_code());
	REQUIRE(create_metal_shader_low_level());
	REQUIRE(create_metal_shader_high_level());
	REQUIRE(create_metal_shader_low_level_multistage());
	REQUIRE(create_metal_shader_high_level_multistage());
	REQUIRE(create_spirv_shader_low_level());
	REQUIRE(create_spirv_shader_multistage());
}
