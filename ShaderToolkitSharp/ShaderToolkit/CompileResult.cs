namespace Ris.ShaderToolkit
{
    /// <summary>
    /// The result of a shader compilation.
    /// </summary>
    public record CompileResult
    {
        /// <summary>
        /// True if the compilation was successful.
        /// </summary>
        public required bool Success { get; set; }

        /// <summary>
        /// The compiled source code.
        /// </summary>
        public string? SourceCode { get; set; } = null;

        /// <summary>
        /// The error message if the compilation failed.
        /// </summary>
        public string? ErrorMessage { get; set; } = null;
    }
}
