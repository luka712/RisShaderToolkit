#ifndef SPIRV_CROSS_COMPILER_H
#define SPIRV_CROSS_COMPILER_H

#include "spirv-cross/spirv_cross_compile_result.hpp"
#include "data/enums.hpp"
#include "util/file_reader.hpp"
#include <map>
#include <compiler/rules.hpp>
#include <spirv_cross/spirv_glsl.hpp>

namespace ris_shader_toolkit {

	class SpirVCrossCompiler
	{
	public:
		//! Constructs a SpirVCrossCompiler object.
		SpirVCrossCompiler();

		//! Compiles a SPIR-V binary file to the specified shading language.
		//! @param spirv The SPIR-V binary data.
		//! @param profile The target shading language profile.
		//! @return A SpirVCrossCompileResult object containing the result of the compilation.
		SpirVCrossCompileResult compile(const std::vector<uint32_t>& spirv, GlslProfile profile, ShaderStage stage);

	protected:
		void handleImageAndSamplersGlsl(spirv_cross::CompilerGLSL& compiler, spirv_cross::ShaderResources& shaderResources);

		//! Handles shader attributes such as input/output variables and their locations for GLSL.
		//! @param vertexCompiler The GLSL compiler instance which will compile vertex shader.
		//! @param fragmentCompiler The GLSL compiler instance which will compile fragment shader.
		//! @param profile The target GLSL profile.
		//! @param stage The shader stage (vertex, fragment, etc.) for which to handle the attributes.
		void handleAttributes(spirv_cross::CompilerGLSL& vertexCompiler, spirv_cross::CompilerGLSL& fragmentCompiler, GlslProfile profile, ShaderStage stage);

		//! Handles uniform variables for GLSL, including uniform buffers and plain uniforms,
		//! and applies necessary transformations based on the target GLSL profile and shader stage.
		//! @param compiler The GLSL compiler instance for which to handle the uniforms.
		void handleUniforms(spirv_cross::CompilerGLSL& compiler);

		//! Compiles SPIR-V binary data to GLSL source code for lower GLSL profiles (e.g., GLSL 3.3, 4.0, etc.) 
		//! where attributes need to be handled differently ( no support for layout(location = {id}) for input/output variables, etc.).
		//! @param spirv The SPIR-V binary data.
		//! @param profile The target GLSL profile.
		//! @param stage The shader stage (vertex, fragment, etc.) for which to compile the GLSL source code.
		SpirVCrossCompileResult compileForLowerProfiles(const std::vector<uint32_t>& spirv, GlslProfile profile, ShaderStage stage);


		FileReader _fileReader;
		std::map<GlslProfile, uint32_t> _glslVersionMap;
		std::map<ShaderStage, spv::ExecutionModel> _executionModelMap;
	};
}

#endif //SPIRV_CROSS_COMPILER_H
