using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RisShaderToolkit.Slang.Enums
{
    /// <summary>
    /// Target format to generate code for.
    /// NOTE: To maintain binary compatibility, do not change existing values! 
    /// Deprecated values are kept with _DEPRECATED suffix.
    /// </summary>
    public enum SlangCompileTarget : int
    {
        SLANG_TARGET_UNKNOWN = 0,
        SLANG_TARGET_NONE = 1,
        SLANG_GLSL = 2,
        SLANG_GLSL_VULKAN_DEPRECATED = 3,          // Deprecated and removed: just use `SLANG_GLSL`.
        SLANG_GLSL_VULKAN_ONE_DESC_DEPRECATED = 4, // Deprecated and removed
        SLANG_HLSL = 5,
        SLANG_SPIRV = 6,
        SLANG_SPIRV_ASM = 7,
        SLANG_DXBC = 8,
        SLANG_DXBC_ASM = 9,
        SLANG_DXIL = 10,
        SLANG_DXIL_ASM = 11,
        SLANG_C_SOURCE = 12,               // The C language
        SLANG_CPP_SOURCE = 13,             // C++ code for shader kernels
        SLANG_HOST_EXECUTABLE = 14,        // Standalone binary executable (CPU/OS)
        SLANG_SHADER_SHARED_LIBRARY = 15,  // Shared library/Dll for shader kernels (CPU/OS)
        SLANG_SHADER_HOST_CALLABLE = 16,   // CPU target to run compiled shader code immediately
        SLANG_CUDA_SOURCE = 17,            // Cuda source
        SLANG_PTX = 18,                    // PTX
        SLANG_CUDA_OBJECT_CODE = 19,       // Object code containing CUDA functions
        SLANG_OBJECT_CODE = 20,            // Object code for later linking
        SLANG_HOST_CPP_SOURCE = 21,        // C++ code for host library or executable
        SLANG_HOST_HOST_CALLABLE = 22,     // Host callable host code (non kernel/shader)
        SLANG_CPP_PYTORCH_BINDING = 23,    // C++ PyTorch binding code
        SLANG_METAL = 24,                  // Metal shading language
        SLANG_METAL_LIB = 25,              // Metal library
        SLANG_METAL_LIB_ASM = 26,          // Metal library assembly
        SLANG_HOST_SHARED_LIBRARY = 27,    // Shared library/Dll for host code (CPU/OS)
        SLANG_WGSL = 28,                   // WebGPU shading language
        SLANG_WGSL_SPIRV_ASM = 29,         // SPIR-V assembly via WGSL
        SLANG_WGSL_SPIRV = 30,             // SPIR-V via WGSL
        SLANG_TARGET_COUNT_OF = 31
    }

}
