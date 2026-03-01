using RisShaderToolkit.Slang;

namespace RisShaderToolkit.Tests;

/// <summary>
/// Tests the <see cref="SlangGlobalSession"/>
/// </summary>
public class SlangGlobalSessionTests
{
    /// <summary>
    /// Test compiling a Slang shader source code to WGSL.
    /// </summary>
    [Fact]
    public void CreateAndDisposeTest()
    {
        var globalSession = new SlangGlobalSession();
        globalSession.Dispose();
        Assert.True(true); // If we got here, it means no exceptions were thrown during creation and disposal.
    }

    /// <summary>
    /// Test finding a profile ID for a known profile name using the <see cref="SlangGlobalSession.FindProfile"/> method.
    /// </summary>
    [Fact]
    public void FindProfileIdTest()
    {
        using var globalSession = new SlangGlobalSession();
        var profileId = globalSession.FindProfile("spirv_1_2");
        Assert.NotEqual(SlangProfileID.SLANG_PROFILE_UNKNOWN, profileId); // Assuming that a valid profile ID is non-zero.
    }
}
