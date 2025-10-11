#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include "process/process.hpp"
#include <iostream>

using namespace shader_toolkit;

// Path to fxc.exe
// TODO: find a better way to locate fxc.exe
const std::string SDK_PATH = "C:\\Program Files (x86)\\Windows Kits\\10\\bin\\10.0.22621.0\\x64\\fxc.exe";

bool proces_compile_hlsl_to_fxc()
{
	std::string input = "D:/Projects/ShaderToolkitSharp/ShaderToolkitC/test_files/sprite_vs.hlsl";
	std::string output = "D:/Projects/ShaderToolkitSharp/ShaderToolkitC/test_files/sprite_vs_fxc.cso";

	std::string fxc_output;
	bool result = shader_toolkit::Process::launchWin(SDK_PATH + " /T vs_5_0 /E main /Fo " + output + " " + input, fxc_output);

	std::cout << "FXC Output: " << fxc_output << std::endl;

	return result;
}


TEST_CASE("process tests", "[proces_compile_hlsl_to_fxc]") {
	REQUIRE(proces_compile_hlsl_to_fxc());
}