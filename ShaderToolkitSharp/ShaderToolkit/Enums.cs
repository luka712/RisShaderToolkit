namespace Ris.ShaderToolkit;

/// <summary>
/// The shader stage.
/// </summary>
public enum ShaderStage
{
    Vertex = 0,
    Fragment = 1,
    Compute = 2
};

/// <summary>
/// The GLSL profile.
/// </summary>
public enum GlslProfile
{
    GLSL_330 = 0,
    GLSL_400 = 1,
    GLSL_410 = 2,
    GLSL_420 = 3,
    GLSL_430 = 4,
    GLSL_440 = 5,
    GLSL_450 = 6,
    GLSL_460 = 7,
    GLES_300 = 8,
    GLES_310 = 9,
    GLES_320 = 10
}
