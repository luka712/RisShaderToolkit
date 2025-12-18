namespace Ris.ShaderToolkit.Json;

/// <summary>
/// The shader JSON representation.
/// </summary>
public class ShaderJson
{
    /// <summary>
    /// The name of the shader.
    /// </summary>
    public string Name { get; set; } = string.Empty;

    /// <summary>
    /// The output file path of the compiled shader.
    /// </summary>
    public string? OutputFile { get; set; }

    /// <summary>
    /// The entry point of the shader. If not specified, defaults to "main".
    /// </summary>
    public string EntryPoint { get; set; } = "main";

    /// <summary>
    /// The stage of the shader to compile. If not specified, defaults to <see cref="ShaderStage.VERTEX"/>.
    /// </summary>
    public ShaderStage Stage { get; set; } = ShaderStage.VERTEX;

    /// <summary>
    /// The target profile for the shader.
    /// </summary>
    public string Profile { get; set; } = string.Empty;

    /// <summary>
    /// The source profile of the shader.
    /// </summary>
    public string SourceProfile { get; set; } = string.Empty;

    /// <summary>
    /// The rules to apply to the shader.
    /// </summary>
    public RulesJson? Rules { get; set; }
}
