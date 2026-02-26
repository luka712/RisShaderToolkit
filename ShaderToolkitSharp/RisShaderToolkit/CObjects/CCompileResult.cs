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
        /// The length of source code if the compilation was successful.
        /// </summary>
        public uint SourceCodeLength { get; set; }

        /// <summary>
        /// The length of binary source code if the compilation was successful.
        /// </summary>
        public uint BinaryCodeLength { get; set; }

        /// <summary>
        /// The length of the error message if the compilation failed.
        /// </summary>
        uint ErrorMessageLength { get; set; }

        /// <summary>
        /// The compiled source code if the compilation was successful.
        /// </summary>
        public IntPtr SourceCode { get; set; }

        /// <summary>
        /// The binary source code if the compilation was successful.
        /// </summary>
        public IntPtr BinarySourceCode { get; set; }

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
            if(BinarySourceCode != IntPtr.Zero)
            {
                Marshal.FreeHGlobal(BinarySourceCode);
                BinarySourceCode = IntPtr.Zero;
            }
            if(ErrorMessage != IntPtr.Zero)
            {
                Marshal.FreeHGlobal(ErrorMessage);
                ErrorMessage = IntPtr.Zero;
            }
        }
    }
}
