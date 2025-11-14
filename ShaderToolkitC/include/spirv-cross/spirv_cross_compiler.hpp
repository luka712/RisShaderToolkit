#ifndef SPIRV_CROSS_COMPILER_H
#define SPIRV_CROSS_COMPILER_H

#include "spirv-cross/spirv_cross_compile_result.hpp"
#include "data/enums.hpp"
#include "util/file_reader.hpp"
#include <map>

namespace ris_shader_toolkit {

	class SpirVCrossCompiler
	{
	public:
		//! Constructs a SpirVCrossCompiler object.
		SpirVCrossCompiler();

		//! Compiles a SPIR-V binary file to the specified shading language.
		//! @param filePath The path to the SPIR-V binary file.
		//! @param profile The target shading language profile.
		//! @return A SpirVCrossCompileResult object containing the result of the compilation.
		SpirVCrossCompileResult compile(const std::string& filePath, GlslProfile profile);

		//! Compiles a SPIR-V binary file to the specified shading language.
		//! @param spirv The SPIR-V binary data.
		//! @param profile The target shading language profile.
		//! @return A SpirVCrossCompileResult object containing the result of the compilation.
		SpirVCrossCompileResult compile(const std::vector<uint32_t>& spirv, GlslProfile profile);

	private:
		FileReader fileReader;
		std::map<GlslProfile, uint32_t> glslVersionMap;
	};
}

#endif //SPIRV_CROSS_COMPILER_H
