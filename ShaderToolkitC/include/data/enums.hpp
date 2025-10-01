//
// Created by lukaa on 1.10.2025..
//

#ifndef ENUMS_H
#define ENUMS_H

namespace shader_toolkit {

   //! The compile target enum.
   enum class CompileTarget {
        HLSL = 0,
        GLSL = 1
    };

   //! The shader stage enum.
    enum class ShaderStage {
        Vertex = 0,
        Fragment = 1,
        Compute = 2
    };

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
}

#endif //ENUMS_H
