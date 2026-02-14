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

        /// <summary>
        /// The input file path used for the compilation.
        /// </summary>
        public string? InputFilePath { get; set; }

        /// <summary>
        /// The GLSL profile used for the compilation if it was compiled to GLSL.
        /// </summary>
        public GlslProfile? GlslProfile { get; set; } = null;

        /// <summary>
        /// The shader stage used for the compilation.
        /// </summary>
        public ShaderStage[]? ShaderStages { get; set; }

        /// <summary>
        /// The entry point of the shader.
        /// </summary>
        public string[]? EntryPoints { get; set; }
    }
}
