using RisShaderToolkit.Rules;

namespace RisShaderToolkit.Dto;

/// <summary>
/// The shader to compile.
/// </summary>
internal record ShaderCompileTaskDto
{
    /// <summary>
    /// The input file path of the shader to compile.
    /// </summary>
    public string InputFilePath { get; set; } = string.Empty;

    /// <summary>
    /// The output file path of the compiled shader.
    /// </summary>
    public string? OutputFilePath { get; set; }

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
    public AnyProfile Profile { get; set; }

    /// <summary>
    /// The source profile of the shader.
    /// </summary>
    public AnyProfile? SourceProfile { get; set; }

    /// <summary>
    /// The input name rule to apply to the shader.
    /// </summary>
    public ReplaceStageInputNameRule? InputNameRule { get; set; }

    /// <summary>
    /// The output name rule to apply to the shader.
    /// </summary>
    public ReplaceStageOutputNameRule? OutputNameRule { get; set; }
}
