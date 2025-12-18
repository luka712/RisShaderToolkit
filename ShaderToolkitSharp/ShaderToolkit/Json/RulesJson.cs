

namespace Ris.ShaderToolkit.Json;

/// <summary>
/// The rules JSON representation.
/// </summary>
public class RulesJson
{
    /// <summary>
    /// The input name rule.
    /// </summary>
    public ReplaceStageInputNameRuleJson? InputNameRule { get; set; }

    /// <summary>
    /// The output name rule.
    /// </summary>
    public ReplaceStageOutputNameRuleJson? OutputNameRule { get; set; }
}
