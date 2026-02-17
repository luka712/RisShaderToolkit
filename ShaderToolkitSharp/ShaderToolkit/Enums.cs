using System.Text.Json.Serialization;

namespace Ris.ShaderToolkit;

/// <summary>
/// The shader stage.
/// </summary>
[JsonConverter(typeof(JsonStringEnumConverter))]
public enum ShaderStage
{
    VERTEX = 0,
    FRAGMENT = 1,
    COMPUTE = 2
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


/// <summary>
/// The shader profile types.
/// </summary>
public enum ProfileType
{
    SLANG = 0,
    HLSL = 1,
    GLSL = 2,
    MSL = 3,
    WGSL = 4
}

/// <summary>
/// The any profile enum.
/// This is used for mapping various profiles in a single enum.
/// </summary>
internal enum AnyProfile
{
    SLANG,
    HLSL,
    GLSL,
    MSL,
    GLSL_330,
    GLSL_400,
    GLSL_410,
    GLSL_420,
    GLSL_430,
    GLSL_440,
    GLSL_450,
    GLSL_460,
    GLES_300,
    GLES_310,
    GLES_320,
    WGSL
}

internal class ProfileResolver
{
    private static Dictionary<AnyProfile, GlslProfile> _glslProfileMap = new ()
    {
        { AnyProfile.GLSL_330, GlslProfile.GLSL_330 },
        { AnyProfile.GLSL_400, GlslProfile.GLSL_400 },
        { AnyProfile.GLSL_410, GlslProfile.GLSL_410 },
        { AnyProfile.GLSL_420, GlslProfile.GLSL_420 },
        { AnyProfile.GLSL_430, GlslProfile.GLSL_430 },
        { AnyProfile.GLSL_440, GlslProfile.GLSL_440 },
        { AnyProfile.GLSL_450, GlslProfile.GLSL_450 },
        { AnyProfile.GLSL_460, GlslProfile.GLSL_460 },
        { AnyProfile.GLES_300, GlslProfile.GLES_300 },
        { AnyProfile.GLES_310, GlslProfile.GLES_310 },
        { AnyProfile.GLES_320, GlslProfile.GLES_320 },
    };

    /// <summary>
    /// Checks if the given <see cref="AnyProfile"/> is a GLSL profile.
    /// </summary>
    /// <param name="profile">The <see cref="AnyProfile"/>.</param>
    /// <param name="glslProfile">The <see cref="GlslProfile"/>.</param>
    /// <returns><c>true</c> if <see cref="GlslProfile"/>, false otherwise.</returns>
    internal static bool IsGlslProfile(AnyProfile profile, out GlslProfile glslProfile)
    {
        if(_glslProfileMap.TryGetValue(profile, out glslProfile))
        {
            return true;
        }
        return false;
    }
}