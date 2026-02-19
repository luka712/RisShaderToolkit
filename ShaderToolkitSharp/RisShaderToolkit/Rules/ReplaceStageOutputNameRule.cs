namespace RisShaderToolkit.Rules;

/// <summary>
/// The rule to replace stage output names.
/// </summary>
public class ReplaceStageOutputNameRule
{
    /// <summary>
    /// The prefix to add to the stage output names.
    /// </summary>
    public string? Prefix { get; set; }

    /// <summary>
    /// Sets whether to trim the entry point name from output variable names.
    /// </summary>
    public bool TrimEntryPointName { get; set; }
}
