#ifndef FXC_COMPILER_H
#define FXC_COMPILER_H

#include "data/enums.hpp"
#include <map>
#include "fxc/fxc_compile_result.hpp"

namespace shader_toolkit {

	/// <summary>
	/// The FxcCompiler class provides functionality to compile HLSL shaders using the fxc.exe compiler.
	/// </summary>
	class FxcCompiler {

	public:

		//! The constructor.
		FxcCompiler();

		//! Compiles an HLSL shader file to a binary using fxc.exe.
		//! @param inputFilePath The path to the input HLSL shader file.
		//! @param outputFilePath The path to the output compiled binary file.
		//! @param shaderStage The shader stage (e.g., ShaderStage::Vertex). Default is ShaderStage::Vertex.
		//! @param profile The HLSL profile to compile to (e.g., HlslProfile::SM_5_0). Default is HlslProfile::SM_5_0.
		//! @param entryPoint The entry point function name (default is "main").
		//! @param columnMajorOrder Whether to use column-major order for matrices (default is true).
		//! @return The result of the compilation as an FxcCompileResult object.
		FxcCompileResult compile(
			const std::string& inputFilePath,
			const std::string& outputFilePath,
			ShaderStage shaderStage = ShaderStage::Vertex,
			HlslProfile profile = HlslProfile::SM_5_0,
			const std::string& entryPoint = "main",
			bool columnMajorOrder = true
		);

	private:
		std::map<ShaderStage, std::map<HlslProfile, std::string >> profileMap;

		//! Tries to find the path to fxc.exe.
		//! @return The path to fxc.exe if found, otherwise an empty string.
		std::string findFxcPath();
	};

}

#endif //FXC_COMPILER_H
