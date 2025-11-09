#ifndef GLSLANG_COMPILER_H
#define GLSLANG_COMPILER_H

#include <string>
#include <map>
#include "data/enums.hpp"
#include <vector>
#include <glslang/Include/glslang_c_interface.h>
#include <glslang/Public/resource_limits_c.h>
#include "util/file_reader.hpp"
#include "glslang_compile_result.hpp"


namespace shader_toolkit {

	//! The GlslangCompiler class provides functionality to compile using glsllang.
	//! Compiles GLSL shader code to SPIR-V binary format.
	class GlslangCompiler
	{
	public:
		//! Constructs a GlslangCompiler object.
		GlslangCompiler();
	

		//! Compiles a GLSL shader file to SPIR-V.
		//! @param filePath The path to the GLSL shader file.
		//! @param stage The shader stage.
		//! @return A GlslangCompileResult object containing the result of the compilation.
		GlslangCompileResult compile(
			const std::string& filePath,
			glslang_stage_t stage
		);

	private:
		FileReader fileReader;

		std::map<ShaderStage, glslang_stage_t> shaderStageMap;
	};
};


#endif // SLANG_SESSION_H