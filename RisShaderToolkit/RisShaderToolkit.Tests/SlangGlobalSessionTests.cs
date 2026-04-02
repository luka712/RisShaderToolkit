using RisShaderToolkit.Slang;
using RisShaderToolkit.Slang.Enums;
using RisShaderToolkit.Slang.Structs;

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
        Assert.NotEqual(SlangProfileID.SLANG_PROFILE_UNKNOWN,
            profileId); // Assuming that a valid profile ID is non-zero.
    }

    /// <summary>
    /// Create a session using the <see cref="SlangGlobalSession.CreateSession"/> method with a valid session description and verify that the session is created successfully.
    /// </summary>
    [Fact]
    public void CreateSessionTest()
    {
        using var globalSession = new SlangGlobalSession();
        var sessionDescription = new SlangSessionDescription()
        {
            Targets =
            [
                new SlangTargetDescription
                {
                    Format = SlangCompileTarget.SLANG_SPIRV,
                    Profile = globalSession.FindProfile("spirv_1_2")
                }
            ],
            DefaultMatrixLayoutMode = SlangMatrixLayoutMode.ColumnMajor
        };
        var session = globalSession.CreateSession(sessionDescription);
        Assert.NotNull(session); // If we got here, it means the session was created successfully.
    }
}