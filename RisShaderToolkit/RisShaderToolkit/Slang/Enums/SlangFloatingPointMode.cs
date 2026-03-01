namespace RisShaderToolkit.Slang.Enums
{
    /// <summary>
    /// Options to control floating-point precision guarantees for a target.
    /// </summary>
    public enum SlangFloatingPointMode : uint
    {
        /// <summary>
        /// Default floating-point behavior.
        /// </summary>
        Default = 0,

        /// <summary>
        /// Allow faster, potentially less precise floating-point operations.
        /// </summary>
        Fast = 1,

        /// <summary>
        /// Ensure precise floating-point behavior.
        /// </summary>
        Precise = 2
    }

}
