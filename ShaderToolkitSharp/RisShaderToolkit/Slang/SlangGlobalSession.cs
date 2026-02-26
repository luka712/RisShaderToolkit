

using System.Runtime.InteropServices;

namespace RisShaderToolkit.Slang
{
    /// <summary>
    /// The Slang global session, which is used to manage the Slang compiler and its resources.
    /// </summary>
    public class SlangGlobalSession : IDisposable
    {
        private const string DLL_NAME = "shader_toolkit_c";

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        static extern SlangResult slang_create_global_session(out IntPtr global_session);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        static extern void slang_release_global_session(IntPtr global_session);

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        static extern SlangProfileID slang_find_profile(IntPtr global_session, IntPtr profile_name);


        //[DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        //static unsafe extern IntPtr compile_slang_to_glsl(
        //    IntPtr compilerPtr,
        //    IntPtr inputFilePath,
        //    GlslProfile glslProfile,
        //    ShaderStage shaderStage,
        //    IntPtr entryPoint,
        //    IntPtr inputRule,
        //    IntPtr outputRule);

        //[DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        //static unsafe extern IntPtr compile_slang_source_code_to_glsl(
        //    IntPtr compilerPtr,
        //    IntPtr slangSourceCode,
        //    GlslProfile glslProfile,
        //    ShaderStage shaderStage,
        //    IntPtr entryPoint,
        //    IntPtr inputRule,
        //    IntPtr outputRule);

        private readonly IntPtr _globalSession;

        /// <summary>
        /// The constructor.
        /// </summary>
        public SlangGlobalSession()
        {
            NativeResolver.Setup();
            _globalSession = new IntPtr();
            SlangResult success = slang_create_global_session(out _globalSession);
            if (success != SlangResult.SLANG_OK)
            {
                Marshal.FreeHGlobal(_globalSession);
                throw new InvalidOperationException("Failed to create Slang global session.");
            }
        }

        public SlangProfileID FindProfile(string profileName)
        {
            IntPtr profileNamePtr = Marshal.StringToHGlobalAnsi(profileName);
            try
            {
                return slang_find_profile(_globalSession, profileNamePtr);
            }
            finally
            {
                Marshal.FreeHGlobal(profileNamePtr);
            }
        }

        /// <inheritdoc/>
        public void Dispose()
        {
            slang_release_global_session(_globalSession);
        }
    }
}
