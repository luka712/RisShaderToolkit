#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include "spirv-cross/spirv_cross_compiler.hpp"
#include "slang/slang_session.hpp"
#include <iostream>

using namespace ris_shader_toolkit;

bool compile_spirv_to_glsl_300_es()
{
	ris_shader_toolkit::SlangSession slangSession;
	slangSession.initialize();
	SlangCompileResult slangResult = slangSession.compileToSpirV("D:/Projects/ShaderToolkitSharp/ShaderToolkitC/test_files/sprite.slang",
		{ ShaderStage::Vertex },
		{ "main_vs" }
	);

	std::vector<uint32_t> input;
	if (slangResult.isSuccess()) {
		// Copy slangResult source code to uint32_t vector
		const std::string& spirvBinary = slangResult.getSourceCode();
		size_t size = spirvBinary.size();
		input.resize(size / sizeof(uint32_t));
		std::memcpy(input.data(), spirvBinary.data(), size);
	}

	ris_shader_toolkit::SpirVCrossCompiler compiler;
	ris_shader_toolkit::SpirVCrossCompileResult result = compiler.compile(input, GlslProfile::GLES_300);
	std::cout << "Glsl Source Code: " << result.getSourceCode() << std::endl;

	return result.isSuccess();
}


TEST_CASE("spirv_cross tests", "[compile_spirv_to_glsl_300_es]") {
	REQUIRE(compile_spirv_to_glsl_300_es());
}
