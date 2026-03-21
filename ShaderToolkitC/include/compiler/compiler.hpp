#ifndef COMPILER_H
#define COMPILER_H

#include "slang/slang_session.hpp"
#include "fxc/fxc_compiler.hpp"
#include "compiler/compile_result.hpp"
#include "rules.hpp"
#include <map>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace ris_shader_toolkit {
	class Compiler {
	public:
		Compiler();


		//! Compiles a Slang shader file to HLSL source code.
		//! @param inputFilePath The path to the input Slang shader file.
		//! @param shaderStage The shader stage (e.g., ShaderStage::Vertex). Default is ShaderStage::Vertex.
		//! @param profile The HLSL profile to compile to (e.g., HlslProfile::SM_5_0). Default is HlslProfile::SM_5_0.
		//! @param entryPoint The entry point function name (default is "main").
		//! @return A CompileResult object containing the result of the compilation.
		//! The result includes success status and source code if successful, or an error message if failed. 
		//! It does not include the output file path.
		/*CompileResult compileSlangToHlsl(
			const std::string& inputFilePath,
			ShaderStage shaderStage = ShaderStage::Vertex,
			HlslProfile profile = HlslProfile::SM_5_0,
			const std::string& entryPoint = "main"
		);*/

		//! Compiles a Slang shader file to a binary using fxc.exe.
		//! @param inputFilePath The path to the input Slang shader file.
		//! @param outputFilePath The path to the output compiled binary file.
		//! @param shaderStage The shader stage (e.g., ShaderStage::Vertex). Default is ShaderStage::Vertex.
		//! @param profile The HLSL profile to compile to (e.g., HlslProfile::SM_5_0). Default is HlslProfile::SM_5_0.
		//! @param entryPoint The entry point function name (default is "main").
		//! @param columnMajorOrder Whether to use column-major order for matrices (default is true).
		//! @return A CompileResult object containing the result of the compilation. 
		//! The result includes success status, output file path, and error message if any. It does not include the source code.
		/*CompileResult compileSlangToFxc(
			const std::string& inputFilePath,
			const std::string& outputFilePath,
			ShaderStage shaderStage = ShaderStage::Vertex,
			HlslProfile profile = HlslProfile::SM_5_0,
			const std::string& entryPoint = "main",
			bool columnMajorOrder = true
		);*/

		//! Compiles a Slang shader file to GLSL source code.
		//! @param sourceCode The Slang shader source code.
		//! @param shaderStage Thee shader stage.
		//! @param entryPoint The entry points for shader stage. Optional if slang source code is decorated with @shader attributes to specify entry point names. If not specified, 'main' will be used as the default entry point name.
		//! @param profile The GLSL profile to compile to (e.g., GlslProfile::GLSL_450). Default is GlslProfile::GLSL_450.
		//! @return A CompileResult object containing the result of the compilation.
		//! The result includes success status and source code if successful, or an error message if failed. 
		CompileResult compileSlangToGlsl(
			const std::string& sourceCode,
			ShaderStage stage,
			std::string entryPoint,
			GlslProfile profile = GlslProfile::GLSL_450
		);

		//! Compiles a Slang shader file to Spir-V source code.
		//! @param sourceCode The Slang shader source code.
		//! @param shaderStages Thee shader stages.
		//! @param entryPoints The entry points for each shader stage. Must be the same size as shaderStages parameter or empty (in which case 'shader' attribute entry point names will be used).
		//! @param profile The Spir-V profile to compile to (e.g., SpirVProfile::SPIRV_1_2). Default is SpirVProfile::SPIRV_1_2.
		//! @return A CompileResult object containing the result of the compilation.
		//! The result includes success status and source code if successful, or an error message if failed. 
		CompileResult compileSlangToSpirV(
			const std::string& sourceCode,
			std::vector<ShaderStage>& stages,
			std::vector<std::string>& entryPoints,
			SpirVProfile profile = SpirVProfile::SPIRV_1_2
		);

		//! Compiles a Slang shader file to Spir-V source code.
		//! @param sourceCode The Slang shader source code.
		//! @param shaderStages Thee shader stages.
		//! @param profile The Spir-V profile to compile to (e.g., SpirVProfile::SPIRV_1_2). Default is SpirVProfile::SPIRV_1_2.
		//! @return A CompileResult object containing the result of the compilation.
		//! The result includes success status and source code if successful, or an error message if failed. 
		CompileResult compileSlangToSpirV(
			const std::string& sourceCode,
			std::vector<ShaderStage>& stages,
			SpirVProfile profile = SpirVProfile::SPIRV_1_2);

		//! Compiles a Slang shader file to WGSL source code.
		//! @param sourceCode The Slang shader source code.
		//! @param shaderStages Thee shader stages.
		//! @param entryPoints The entry points for each shader stage. Must be the same size as shaderStages parameter or empty (in which case 'shader' attribute entry point names will be used).
		CompileResult compileSlangToWgsl(
			const std::string& sourceCode,
			const std::vector<ShaderStage> stages,
			const std::vector<std::string> entryPoints
		);

		//! Compiles a Slang shader file to WGSL source code.
		//! @param sourceCode The Slang shader source code.
		//! @param shaderStages Thee shader stages.
		//! @param entryPoints The entry points for each shader stage. Must be the same size as shaderStages parameter or empty (in which case 'shader' attribute entry point names will be used).
		CompileResult compileSlangToWgsl(
			const std::string& sourceCode,
			std::vector<ShaderStage>& stages
		);

	private:
		FxcCompiler _fxcCompiler;
		static std::shared_ptr<spdlog::logger> _logger;

		//! Creates a file with the specified content.
		//! @param filePath The path to the file to create.
		//! @param content The content to write to the file.
		// bool createFile(const std::string& filePath, const std::string& content);
	};
}

#endif //COMPILER_H
