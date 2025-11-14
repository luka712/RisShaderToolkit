#include "spirv-cross/spirv_cross_compiler.hpp"
#include <spirv_cross/spirv_glsl.hpp>

namespace ris_shader_toolkit {

	SpirVCrossCompiler::SpirVCrossCompiler() {
		glslVersionMap = {
			{ GlslProfile::GLSL_330, 330 },
			{ GlslProfile::GLSL_400, 400 },
			{ GlslProfile::GLSL_410, 410 },
			{ GlslProfile::GLSL_420, 420 },
			{ GlslProfile::GLSL_430, 430 },
			{ GlslProfile::GLSL_440, 440 },
			{ GlslProfile::GLSL_450, 450 },
			{ GlslProfile::GLSL_460, 460 },
			{ GlslProfile::GLES_300, 300 },
			{ GlslProfile::GLES_310, 310 },
			{ GlslProfile::GLES_320, 320 }
		};
	}

	SpirVCrossCompileResult SpirVCrossCompiler::compile(const std::string& filePath, GlslProfile profile) {

		// Load SPIR-V
		std::vector<uint32_t> spirv = fileReader.readAsU32(filePath);
		return compile(spirv, profile);
	}

	SpirVCrossCompileResult SpirVCrossCompiler::compile(const std::vector<uint32_t>& spirv, GlslProfile profile) {
		// Load SPIR-V
		try {
			spirv_cross::CompilerGLSL compiler(spirv);
			// Set GLSL options
			spirv_cross::CompilerGLSL::Options options;
			options.version = glslVersionMap[profile];
			options.force_zero_initialized_variables = false;
			if (profile == GlslProfile::GLES_300 || profile == GlslProfile::GLES_310 || profile == GlslProfile::GLES_320) {
				options.es = true;
			}
		
			compiler.set_common_options(options);

			// Get shader resources
			spirv_cross::ShaderResources resources = compiler.get_shader_resources();

			// Rename the uniform buffer to "c_viewProjection"
			for (auto& ub : resources.uniform_buffers)
			{
				// glsl.set_name(ub.id, "c_viewProjection");

				// Flatten the array-of-vec4 into a mat4
				// compiler.flatten_buffer_block(ub.id);
			}

			// Compile to GLSL
			std::string glslSource = compiler.compile();
			return SpirVCrossCompileResult(true, glslSource, "");
		}
		catch (const std::exception& e) {
			return SpirVCrossCompileResult(false, "", e.what());
		}
	}
} // namespace ris_shader_toolkit