#include "fxc/fxc_compiler.hpp"
#include <filesystem>
#include "process/process.hpp"
#include <fstream>

namespace shader_toolkit {

	FxcCompiler::FxcCompiler()
	{
		profileMap[ShaderStage::Vertex] = {
			{ HlslProfile::SM_4_0, "vs_4_0" },
			{ HlslProfile::SM_4_1, "vs_4_1" },
			{ HlslProfile::SM_5_0, "vs_5_0" },
			{ HlslProfile::SM_5_1, "vs_5_1" },
			{ HlslProfile::SM_6_0, "vs_6_0" },
			{ HlslProfile::SM_6_1, "vs_6_1" },
			{ HlslProfile::SM_6_2, "vs_6_2" },
			{ HlslProfile::SM_6_3, "vs_6_3" },
			{ HlslProfile::SM_6_4, "vs_6_4" },
			{ HlslProfile::SM_6_5, "vs_6_5" }
		};

		profileMap[ShaderStage::Fragment] = {
			{ HlslProfile::SM_4_0, "ps_4_0" },
			{ HlslProfile::SM_4_1, "ps_4_1" },
			{ HlslProfile::SM_5_0, "ps_5_0" },
			{ HlslProfile::SM_5_1, "ps_5_1" },
			{ HlslProfile::SM_6_0, "ps_6_0" },
			{ HlslProfile::SM_6_1, "ps_6_1" },
			{ HlslProfile::SM_6_2, "ps_6_2" },
			{ HlslProfile::SM_6_3, "ps_6_3" },
			{ HlslProfile::SM_6_4, "ps_6_4" },
			{ HlslProfile::SM_6_5, "ps_6_5" }
		};
	}

	std::string FxcCompiler::findFxcPath()
	{
		// Should be something like this C:\\Program Files (x86)\\Windows Kits\\10\\bin\\10.0.22621.0\\x64\\fxc.exe

		// Base path to the Windows SDK
		const std::string SDK_PATH = "C:\\Program Files (x86)\\Windows Kits\\10\\bin\\";

		// Now we can go through the directories to find the highest version and if it contains fxc.exe
		// This will give us directories like "10.0.22621.0"
		for (const auto& entry : std::filesystem::directory_iterator(SDK_PATH))
		{
			// In each version directory, we look for the x64 directory and then fxc.exe
			if (entry.is_directory())
			{
				std::string binPath = entry.path().string() + "\\x64\\fxc.exe";
				if (std::filesystem::exists(binPath))
				{
					return binPath;
				}
			}
		}

		return "";
	}

	FxcCompileResult FxcCompiler::compile(
		const std::string& inputFilePath,
		const std::string& outputFilePath,
		ShaderStage shaderStage,
		HlslProfile profile,
		const std::string& entryPoint,
		bool columnMajorOrder
		)
	{
		std::string profileStr = profileMap[shaderStage][profile];

		std::string fxcPath = findFxcPath();
		if (fxcPath.empty())
		{
			return FxcCompileResult::errorResult("Could not find fxc.exe. Please ensure that the Windows SDK is installed.");
		}

		// Construct the command to run fxc.exe
		std::string majorOrder = columnMajorOrder ? " /Zpc " : " /Zpr ";

		std::string command = "\"" + fxcPath + "\" /T " + profileStr + " /E " + entryPoint + majorOrder +
			" /Fo \"" + outputFilePath + "\" \"" + inputFilePath + "\"";
		std::string output;
		bool success = Process::launchWin(command, output);
		if (!success)
		{
			return FxcCompileResult::errorResult("Failed to execute fxc.exe. Command: " + command + ". Output: " + output);
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
			return FxcCompileResult::errorResult("Compilation failed. fxc.exe output: " + output);
		}

		return FxcCompileResult::successResult(sourceCode);
	}
}