#ifndef ENUMS_H
#define ENUMS_H

namespace ris_shader_toolkit {

   //! The compile target enum.
   enum class CompileTarget {
        HLSL = 0,
        GLSL = 1,
		Metal = 2,
    };

   //! The shader stage enum.
    enum class ShaderStage {
        Vertex = 0,
        Fragment = 1,
        Compute = 2
    };

    //! The HLSL profile enum.
    enum class HlslProfile {
        SM_4_0 = 0,
        SM_4_1 = 1,
        SM_5_0 = 2,
        SM_5_1 = 3,
        SM_6_0 = 4,
        SM_6_1 = 5,
        SM_6_2 = 6,
        SM_6_3 = 7,
        SM_6_4 = 8,
        SM_6_5 = 9
    };

    //! The GLSL profile enum.
    enum class GlslProfile {
        GLSL_330 = 0,
        GLSL_400 = 1,
        GLSL_410 = 2,
        GLSL_420 = 3,
        GLSL_430 = 4,
        GLSL_440 = 5,
        GLSL_450 = 6,
        GLSL_460 = 7,
        GLES_300 = 8,
        GLES_310 = 9,
        GLES_320 = 10
   	};

    //! The SpirV profile enum.
    enum class SpirVProfile {
        SPIRV_1_0 = 0,
        SPIRV_1_1 = 1,
        SPIRV_1_2 = 2,
        SPIRV_1_3 = 3,
        SPIRV_1_4 = 4,
        SPIRV_1_5 = 5,
        SPIRV_1_6 = 6
    };

    //! The Metal profile enum.
    enum class MetalProfile {
        MSL_1_0 = 0,
        MSL_1_1 = 1,
        MSL_1_2 = 2,
        MSL_2_0 = 3,
        MSL_2_1 = 4,
        MSL_2_2 = 5,
        MSL_2_3 = 6,
        MSL_2_4 = 7
	};

    //! The Apple SDK enum.
    //! Used to specify the target Apple platform for Metal shader compilation to .metallib and .air files.
    //! The -sdk argument in xcrun requires specifying the target platform.
    enum class AppleSdk {
        iOS = 0,
        macOS = 1,
        tvOS = 2,
        watchOS = 3,
        iOS_Simulator = 4,
    };

	//! The type of shader binding.
    enum class BindingType {
        UniformBuffer,
        Resource,
        SamplerState,
    };
}

#endif //ENUMS_H
