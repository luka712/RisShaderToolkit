namespace RisShaderToolkit.Json;

/// <summary>
/// The compile JSON representation.
/// </summary>
public class CompileJson
{
    /// <summary>
    /// The version of the compile JSON.
    /// </summary>
    public string Version { get; set; } = "0.0.1";

    /// <summary>
    /// The list of shaders to compile.
    /// </summary>
    public List<ShaderJson> Shaders { get; set; } = new List<ShaderJson>();
}
