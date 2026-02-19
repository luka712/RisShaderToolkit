using System.Runtime.InteropServices;

namespace RisShaderToolkit.CObjects
{
    /// <summary>
    /// The compile result from the C/C++ library.
    /// </summary>
    [StructLayout(LayoutKind.Sequential)]
    internal struct CCompileResult : IDisposable
    {
        /// <summary>
        /// Indicates whether the compilation was successful.
        /// </summary>
        public bool Success { get; set; }

        /// <summary>
        /// The compiled source code if the compilation was successful.
        /// </summary>
        public IntPtr SourceCode { get; set; }

        /// <summary>
        /// The output file path if applicable.
        /// </summary>
        public IntPtr OutputFilePath { get; set; }

        /// <summary>
        /// The error message if the compilation failed.
        /// </summary>
        public IntPtr ErrorMessage { get; set; }

        /// <inheritdoc/>
        public void Dispose()
        {
            if(SourceCode != IntPtr.Zero)
            {
                Marshal.FreeHGlobal(SourceCode);
                SourceCode = IntPtr.Zero;
            }
            if(OutputFilePath != IntPtr.Zero)
            {
                Marshal.FreeHGlobal(OutputFilePath);
                OutputFilePath = IntPtr.Zero;
            }
            if(ErrorMessage != IntPtr.Zero)
            {
                Marshal.FreeHGlobal(ErrorMessage);
                ErrorMessage = IntPtr.Zero;
            }
        }
    }
}
