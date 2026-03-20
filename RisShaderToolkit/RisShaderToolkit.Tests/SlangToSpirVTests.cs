namespace RisShaderToolkit.Tests;

/// <summary>
/// Tests for compiling Slang shaders to SPIR-V.
/// </summary>
public class SlangToSpirVTests
{
    /// <summary>
    /// Test compiling a Slang shader source code to SPIR-V.
    /// </summary>
    [Fact]
    public void TestCompileSlangToSpirV()
    {
        // Arrange
        ShaderCompiler compiler = new ShaderCompiler();
        string slangSourceCode = File.ReadAllText("Data/sprite.slang");
        // Act
        CompileResult vertexResult = compiler.CompileSlangToSpirV(slangSourceCode, 
            ShaderStage.VERTEX,
            SpirVProfile.SPIRV_1_2, 
            "main_vs");
        
        Assert.True(vertexResult.Success);
        Assert.NotNull(vertexResult.BinarySourceCode);
        Assert.True(vertexResult.BinarySourceCode.Length > 0);

        // Act
        CompileResult fragmentResult = compiler.CompileSlangToSpirV(slangSourceCode,
            ShaderStage.FRAGMENT,
            SpirVProfile.SPIRV_1_2,
            "main_fs");

        Assert.True(fragmentResult.Success);
        Assert.NotNull(fragmentResult.BinarySourceCode);
        Assert.True(fragmentResult.BinarySourceCode.Length > 0);
    }

    /// <summary>
    /// Test compiling a Slang shader source code to SPIR-V.
    /// </summary>
    [Fact]
    public void TestCompileSlangToSpirV2()
    {
        // Arrange
        ShaderCompiler compiler = new ShaderCompiler();
        string slangSourceCode = File.ReadAllText("Data/sprite.slang");
        // Act
        CompileResult vertexResult = compiler.CompileSlangToSpirV(slangSourceCode, ShaderStage.VERTEX);
        Assert.True(vertexResult.Success);
        Assert.NotNull(vertexResult.BinarySourceCode);
        Assert.True(vertexResult.BinarySourceCode.Length > 0);

        CompileResult fragmentResult = compiler.CompileSlangToSpirV(slangSourceCode, ShaderStage.VERTEX);
        Assert.True(fragmentResult.Success);
        Assert.NotNull(fragmentResult.BinarySourceCode);
        Assert.True(fragmentResult.BinarySourceCode.Length > 0);
    }

    /// <summary>
    /// Compiles shaders from a JSON file. 
    /// Tests Slang to SpirV JSON compilation.
    /// </summary>
    [Fact]
    public void TestCompileSpirVJson()
    {
        // TODO: fix when removing automapper.

        // Arrange
        ShaderCompiler compiler = new ShaderCompiler();
        string jsonFilePath = "Data/compile_slang_to_spirv.json";
        // Act
        compiler.CompileFromJson(jsonFilePath);
        // If we reach this point, the compilation was successful.
        Assert.True(true);
        foreach (var result in compiler.CompileFromJson(jsonFilePath).Results)
        {
            Assert.True(result.Success);
        }
    }
}
