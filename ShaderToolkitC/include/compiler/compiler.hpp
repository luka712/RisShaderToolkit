#ifndef COMPILER_H
#define COMPILER_H

#include "slang/slang_session.hpp"
#include "fxc/fxc_compiler.hpp"
#include "compiler/compile_result.hpp"
#include "rules.hpp"

namespace ris_shader_toolkit {
    class Compiler {
    public:
        Compiler();

        //! Compiles a Slang shader file to Spir-V source code.
        //! @param inputFilePath The path to the input Slang shader file.
        //! @param shaderStage The shader stage (e.g., ShaderStage::Vertex). Default is ShaderStage::Vertex.
        //! @param profile The Spir-V profile to compile to (e.g., SpirVProfile::SPIRV_1_2). Default is SpirVProfile::SPIRV_1_2.
        //! @param entryPoint The entry point function name (default is "main").
        //! @return A CompileResult object containing the result of the compilation.
        //! The result includes success status and source code if successful, or an error message if failed. 
        //! It does not include the output file path.
        CompileResult compileSlangToSpirV(
            const std::string& inputFilePath,
            ShaderStage shaderStage = ShaderStage::Vertex,
            SpirVProfile profile = SpirVProfile::SPIRV_1_2,
            const std::string& entryPoint = "main"
            );

        //! Compiles a Slang shader file to Spir-V source code.
        //! @param slangSourceCode The Slang source code.
        //! @param shaderStage The shader stage (e.g., ShaderStage::Vertex). Default is ShaderStage::Vertex.
        //! @param profile The Spir-V profile to compile to (e.g., SpirVProfile::SPIRV_1_2). Default is SpirVProfile::SPIRV_1_2.
        //! @param entryPoint The entry point function name (default is "main").
        //! @return A CompileResult object containing the result of the compilation.
        //! The result includes success status and source code if successful, or an error message if failed. 
        //! It does not include the output file path.
        CompileResult compileSlangSourceToSpirV(
            const std::string& slangSourceCode,
            ShaderStage shaderStage = ShaderStage::Vertex,
            SpirVProfile profile = SpirVProfile::SPIRV_1_2,
            const std::string& entryPoint = "main"
        );

		//! Compiles a Slang shader file to HLSL source code.
		//! @param inputFilePath The path to the input Slang shader file.
		//! @param shaderStage The shader stage (e.g., ShaderStage::Vertex). Default is ShaderStage::Vertex.
		//! @param profile The HLSL profile to compile to (e.g., HlslProfile::SM_5_0). Default is HlslProfile::SM_5_0.
		//! @param entryPoint The entry point function name (default is "main").
		//! @return A CompileResult object containing the result of the compilation.
		//! The result includes success status and source code if successful, or an error message if failed. 
        //! It does not include the output file path.
        CompileResult compileSlangToHlsl(
            const std::string& inputFilePath,
            ShaderStage shaderStage = ShaderStage::Vertex,
            HlslProfile profile = HlslProfile::SM_5_0,
            const std::string& entryPoint = "main"
		);

        //! Compiles a Slang shader file to a binary using fxc.exe.
        //! @param inputFilePath The path to the input Slang shader file.
        //! @param outputFilePath The path to the output compiled binary file.
        //! @param shaderStage The shader stage (e.g., ShaderStage::Vertex). Default is ShaderStage::Vertex.
        //! @param profile The HLSL profile to compile to (e.g., HlslProfile::SM_5_0). Default is HlslProfile::SM_5_0.
        //! @param entryPoint The entry point function name (default is "main").
        //! @param columnMajorOrder Whether to use column-major order for matrices (default is true).
		//! @return A CompileResult object containing the result of the compilation. 
		//! The result includes success status, output file path, and error message if any. It does not include the source code.
        CompileResult compileSlangToFxc(
            const std::string& inputFilePath,
            const std::string& outputFilePath,
            ShaderStage shaderStage = ShaderStage::Vertex,
            HlslProfile profile = HlslProfile::SM_5_0,
            const std::string& entryPoint = "main",
            bool columnMajorOrder = true
        );

        //! Compiles a Slang shader file to GLSL source code.
        //! @param inputFilePath The path to the input Slang shader file.
        //! @param profile The GLSL profile to compile to (e.g., GlslProfile::GLSL_450). Default is GlslProfile::GLSL_450.
        //! @param shaderStage The shader stage (e.g., ShaderStage::Vertex). Default is ShaderStage::Vertex.
        //! @param entryPoint The entry point function name (default is "main").
        //! @param inputRule An optional rule to replace stage input names.
		//! @param outputRule An optional rule to replace stage output names.
        //! @return A CompileResult object containing the result of the compilation.
        CompileResult compileSlangToGlsl(
			const std::string& inputFilePath,
			GlslProfile profile = GlslProfile::GLSL_450,
			ShaderStage shaderStage = ShaderStage::Vertex,
			const std::string& entryPoint = "main",
            ReplaceStageInputNameRule* inputRule = nullptr,
			ReplaceStageOutputNameRule* outputRule = nullptr
		);

        //! Compiles a Slang shader file to GLSL source code.
        //! @param slangSource The slang shader source code..
        //! @param profile The GLSL profile to compile to (e.g., GlslProfile::GLSL_450). Default is GlslProfile::GLSL_450.
        //! @param shaderStage The shader stage (e.g., ShaderStage::Vertex). Default is ShaderStage::Vertex.
        //! @param entryPoint The entry point function name (default is "main").
        //! @param inputRule An optional rule to replace stage input names.
		//! @param outputRule An optional rule to replace stage output names.
        //! @return A CompileResult object containing the result of the compilation.
        CompileResult compileSlangSourceToGlsl(
			const std::string& slangSource,
			GlslProfile profile = GlslProfile::GLSL_450,
			ShaderStage shaderStage = ShaderStage::Vertex,
			const std::string& entryPoint = "main",
            ReplaceStageInputNameRule* inputRule = nullptr,
			ReplaceStageOutputNameRule* outputRule = nullptr
		);

        private:
          FxcCompiler fxcCompiler;

		  //! Creates a file with the specified content.
		  //! @param filePath The path to the file to create.
		  //! @param content The content to write to the file.
		  bool createFile(const std::string& filePath, const std::string& content);
    };
}

#endif //COMPILER_H
