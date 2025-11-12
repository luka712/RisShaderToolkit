#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include "process/process.hpp"
#include <iostream>

using namespace ris_shader_toolkit;

// Path to fxc.exe
// TODO: find a better way to locate fxc.exe
const std::string SDK_PATH = "C:\\Program Files (x86)\\Windows Kits\\10\\bin\\10.0.22621.0\\x64\\fxc.exe";

bool process_compile_hlsl_to_fxc()
{
#if _WIN32
	std::string input = "D:/Projects/ShaderToolkitSharp/ShaderToolkitC/test_files/sprite_vs.hlsl";
	std::string output = "D:/Projects/ShaderToolkitSharp/ShaderToolkitC/test_files/sprite_vs_fxc.cso";

	std::string fxc_output;
	bool result = ris_shader_toolkit::Process::launchWin(SDK_PATH + " /T vs_5_0 /E main /Fo " + output + " " + input, fxc_output);

	std::cout << "FXC Output: " << fxc_output << std::endl;

	return result;
#else
	return true; // No need to run on non-Windows platforms
#endif
}

bool process_compile_metal_to_air()
{
	// xcrun is only available on macOS
#if __APPLE__
	std::string input = "D:/Projects/ShaderToolkitSharp/ShaderToolkitC/test_files/sprite.metal";
	std::string output = "D:/Projects/ShaderToolkitSharp/ShaderToolkitC/test_files/sprite.air";

	std::string xcrun_output;
	bool result = ris_shader_toolkit::Process::launchMac("xcrun -sdk macosx metal " + input + " -o " + output, xcrun_output);

	std::cout << "xcrun Output: " << xcrun_output << std::endl;

	return result;
#else 
	return true;
#endif 
}

TEST_CASE("process tests", "[process_compile_hlsl_to_fxc], [process_compile_metal_to_air]") {
	REQUIRE(process_compile_hlsl_to_fxc());
	REQUIRE(process_compile_metal_to_air());
}