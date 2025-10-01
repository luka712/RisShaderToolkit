#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include "slang/slang_session.hpp"

using namespace shader_toolkit;

bool create_slang_session()
{
	shader_toolkit::SlangSession session;
	return session.initialize();
}

bool create_hlsl_shader_low_level()
{
	shader_toolkit::SlangSession session;
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
	shader_toolkit::SlangSession session;
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

TEST_CASE("slang tests", "[create_slang_session], [create_hlsl_shader_low_level], [create_hlsl_shader_high_level]") {
	REQUIRE(create_slang_session());
	REQUIRE(create_hlsl_shader_low_level());
	REQUIRE(create_hlsl_shader_high_level());
}