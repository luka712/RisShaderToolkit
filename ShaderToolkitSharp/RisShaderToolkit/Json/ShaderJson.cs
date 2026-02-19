namespace RisShaderToolkit.Json;

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
    /// The entry point of the shader.
    /// </summary>
    public string[]? EntryPoints { get; set; }

    /// <summary>
    /// The stage of the shader to compile. 
    /// </summary>
    public ShaderStage[]? Stages { get; set; }

    /// <summary>
    /// The target profile for the shader.
    /// </summary>
    public string Profile { get; set; } = String.Empty;

    /// <summary>
    /// The source profile of the shader.
    /// </summary>
    public string? SourceProfile { get; set; } = string.Empty;

    /// <summary>
    /// The rules to apply to the shader.
    /// </summary>
    public RulesJson? Rules { get; set; }
}
