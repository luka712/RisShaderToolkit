using System.Runtime.InteropServices;

namespace ShaderToolkit
{
    /// <summary>
    /// Compiles glsl to glsl using shaderc.
    /// </summary>
    public class GlslToGlslShaderCCompiler
    {
        [DllImport("shader_toolkit_bindings", CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr glsl_to_glsl_shaderc_compiler_new();

        [DllImport("shader_toolkit_bindings", CallingConvention = CallingConvention.Cdecl)]
        static extern void glsl_to_glsl_shaderc_compiler_free(IntPtr compiler);

        [DllImport("shader_toolkit_bindings", CallingConvention = CallingConvention.Cdecl)]
        static extern bool glsl_to_glsl_shaderc_compiler_compile_from_file(
            IntPtr compiler,
            IntPtr filename,
            IntPtr fileoutput,
            IntPtr in_glsl_profile,
            IntPtr out_glsl_profile,
            IntPtr out_code,
            out IntPtr error_message);

        [DllImport("shader_toolkit_bindings", CallingConvention = CallingConvention.Cdecl)]
        static extern unsafe IntPtr glsl_to_glsl_shaderc_compiler_compile_from_source(
            IntPtr compiler,
            IntPtr sourceCode,
            IntPtr inGlslProfile,
            IntPtr outGlslProfile);

        [DllImport("shader_toolkit_bindings", CallingConvention = CallingConvention.Cdecl)]
        static extern unsafe void glsl_to_glsl_shaderc_compiler_get_last_error(char* errorMessage, long* errorMessageLength);

        [DllImport("shader_toolkit_bindings", CallingConvention = CallingConvention.Cdecl)]
        static extern unsafe void free_complied_code(IntPtr compiledCode);

        /// <summary>
        /// The constructor for the <see cref="GlslToGlslShaderCCompiler"/>.
        /// </summary>
        public GlslToGlslShaderCCompiler()
        {
            NativePtr = glsl_to_glsl_shaderc_compiler_new();
        }

        /// <summary>
        /// Gets the native pointer to the compiler.
        /// </summary>
        public IntPtr NativePtr { get; private set; }

        public bool CompilelslToGlsl(string sourceCode, string inGlslProfile, string outGlslProfile, 
            out string? targetCode,
            out string? errorMessage)
        {
            unsafe
            {
                IntPtr sourceCodePtr = Marshal.StringToHGlobalAnsi(sourceCode);
                IntPtr inGlslProfilePtr = Marshal.StringToHGlobalAnsi(inGlslProfile);
                IntPtr outGlslProfilePtr = Marshal.StringToHGlobalAnsi(outGlslProfile);

                IntPtr result = glsl_to_glsl_shaderc_compiler_compile_from_source(
                        NativePtr,
                        sourceCodePtr,
                        inGlslProfilePtr,
                        outGlslProfilePtr);

                Marshal.FreeHGlobal(sourceCodePtr);
                Marshal.FreeHGlobal(inGlslProfilePtr);
                Marshal.FreeHGlobal(outGlslProfilePtr);

                if (result == IntPtr.Zero)
                {
                    errorMessage = GetErrorMsg();
                    targetCode = null;
                    return false;
                }

                targetCode = Marshal.PtrToStringAnsi(result);
                errorMessage = null;
                free_complied_code(result);
 
            }
            return true;
        }

        private string GetErrorMsg()
        {
            unsafe
            {
                long errorMessageLength = 0;
                glsl_to_glsl_shaderc_compiler_get_last_error(null, &errorMessageLength);
                if (errorMessageLength > 0)
                {
                    char* errorMessage = stackalloc char[(int)errorMessageLength];
                    glsl_to_glsl_shaderc_compiler_get_last_error(errorMessage, &errorMessageLength);
                    return Marshal.PtrToStringAnsi((IntPtr)errorMessage, (int)errorMessageLength);
                }
                else
                {
                    return string.Empty;
                }
            }
        }
    }
}
