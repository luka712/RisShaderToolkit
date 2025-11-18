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
		//! @param filePath The path to the SPIR-V binary file.
		//! @param profile The target shading language profile.
		//! @param replaceStageInputNameRule An optional rule to replace stage input names.
		//! @param replaceStageOutputNameRule An optional rule to replace stage output names.
		//! @return A SpirVCrossCompileResult object containing the result of the compilation.
		SpirVCrossCompileResult compile(const std::string& filePath, GlslProfile profile,
			ReplaceStageInputNameRule* replaceStageInputNameRule = nullptr,
			ReplaceStageOutputNameRule* replaceStageOutputNameRule = nullptr
		);

		//! Compiles a SPIR-V binary file to the specified shading language.
		//! @param spirv The SPIR-V binary data.
		//! @param profile The target shading language profile.
		//! @param replaceStageInputNameRule An optional rule to replace stage input names.
		//! @param replaceStageOutputNameRule An optional rule to replace stage output names.
		//! @return A SpirVCrossCompileResult object containing the result of the compilation.
		SpirVCrossCompileResult compile(const std::vector<uint32_t>& spirv, GlslProfile profile,
			ReplaceStageInputNameRule* replaceStageInputNameRule = nullptr,
			ReplaceStageOutputNameRule* replaceStageOutputNameRule = nullptr
		);


	protected:
		FileReader fileReader;
		std::map<GlslProfile, uint32_t> glslVersionMap;

		void applyReplaceStageInputNameRule(
			spirv_cross::CompilerGLSL& compiler,
			spirv_cross::ShaderResources& shaderResources,
			ReplaceStageInputNameRule* replaceStageInputNameRule);

		void applyReplaceStageOutputNameRule(
			spirv_cross::CompilerGLSL& compiler,
			spirv_cross::ShaderResources& shaderResources,
			ReplaceStageOutputNameRule* replaceStageOutputNameRule);

		void handleImageAndSamplersGlsl(
			spirv_cross::CompilerGLSL& compiler,
			spirv_cross::ShaderResources& shaderResources);
	};
}

#endif //SPIRV_CROSS_COMPILER_H
