namespace RisShaderToolkit.Slang.Enums
{
    /// <summary>
    /// Options to control emission of `#line` directives in generated code.
    /// </summary>
    public enum SlangLineDirectiveMode : uint
    {
        /// <summary>
        /// Default behavior: pick behavior based on target.
        /// </summary>
        Default = 0,

        /// <summary>
        /// Don't emit line directives at all.
        /// </summary>
        None = 1,

        /// <summary>
        /// Emit standard C-style `#line` directives.
        /// </summary>
        Standard = 2,

        /// <summary>
        /// Emit GLSL-style directives with file *number* instead of name.
        /// </summary>
        GLSL = 3,

        /// <summary>
        /// Use a source map to track line mappings (no `#line` will appear in emitted source).
        /// </summary>
        SourceMap = 4
    }

}
