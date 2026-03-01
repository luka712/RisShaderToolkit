using RisShaderToolkit.Slang;
using RisShaderToolkit.Slang.Enums;
using RisShaderToolkit.Slang.Structs;

namespace RisShaderToolkit.Tests;

/// <summary>
/// Tests the Slang default structures and enums, such as <see cref="SlangTargetDescription"/>, <see cref="SlangCompileTarget"/>, and <see cref="SlangTargetFlags"/>.
/// </summary>
public class SlangStructsTests
{
    /// <summary>
    /// Test compiling a Slang shader source code to WGSL.
    /// </summary>
    [Fact]
    public void CreateTargetDescriptionTest()
    {
        var targetDescription = new SlangTargetDescription();

        Assert.Equal(SlangCompileTarget.SLANG_TARGET_UNKNOWN, targetDescription.Format);
        Assert.Equal(SlangProfileID.SLANG_PROFILE_UNKNOWN, targetDescription.Profile);
    }

   
}
