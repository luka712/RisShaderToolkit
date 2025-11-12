#include "xcrun/xcrun_compiler.hpp"
#include "process/process.hpp"
#include <filesystem>
#include <fstream>

namespace ris_shader_toolkit {

	XcrunCompiler::XcrunCompiler()
	{
		mapSdk = {
			{ AppleSdk::macOS, "macosx" },
			{ AppleSdk::iOS, "iphoneos" },
			{ AppleSdk::tvOS, "appletvos" },
			{ AppleSdk::watchOS, "watchos" },
			{ AppleSdk::iOS_Simulator, "iphonesimulator" }
		};
	}

	XcrunCompileResult XcrunCompiler::compileIntermediateToMetallib(
		const std::string& inputFilePath,
		const std::string& outputFilePath,
		AppleSdk sdk) {

		throw new std::runtime_error("Not implemented yet.");
	}

	XcrunCompileResult XcrunCompiler::compileMetalToIntermediate(
		const std::string& inputFilePath,
		const std::string& outputFilePath,
		AppleSdk sdk) {

		std::string sdkStr = mapSdk[sdk];

		std::string command = "xcrun -sdk " + sdkStr + " metal " + inputFilePath + " -o " + outputFilePath;
		std::string output;
		bool success = Process::launchWin(command, output);
		if (!success)
		{
			return XcrunCompileResult::errorResult("Failed to execute fxc.exe. Command: " + command + ". Output: " + output);
		}

		// Read the output file if compilation was successful.
		std::string sourceCode = "";
		if (std::filesystem::exists(outputFilePath))
		{
			std::ifstream ifs(outputFilePath);
			sourceCode.assign((std::istreambuf_iterator<char>(ifs)),
				(std::istreambuf_iterator<char>()));
		}
		else
		{
			return XcrunCompileResult::errorResult("Compilation failed. fxc.exe output: " + output);
		}

		return XcrunCompileResult::successResult(sourceCode);
	}

}
