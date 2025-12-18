namespace Ris.ShaderToolkit.Json;

/// <summary>
/// The output name rule JSON representation.
/// </summary>
public class ReplaceStageOutputNameRuleJson
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
