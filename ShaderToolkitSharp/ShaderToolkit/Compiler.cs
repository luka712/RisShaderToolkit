

using System.Runtime.InteropServices;

namespace Ris.ShaderToolkit
{


    /// <summary>
    /// The shader compiler.
    /// </summary>
    public class Compiler : IDisposable
    {
        private const string DLL_NAME = "shader_toolkit_c.dll";

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        static extern IntPtr create_compiler();

        [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
        static extern void free_compiler(IntPtr compiler);

      

        private readonly IntPtr NativePtr;

        /// <summary>
        /// The constructor for the <see cref="Compiler"/>.
        /// </summary>
        public Compiler()
        {
            NativePtr = create_compiler();
            if(NativePtr == IntPtr.Zero)
            {
                throw new InvalidOperationException("Failed to create compiler.");
            }
        }

        public void Dispose()
        {
            free_compiler(NativePtr);
        }


    }
}
