namespace RisShaderToolkit.Tests;

/// <summary>
/// Tests for compiling Slang shaders to WGSL.
/// </summary>
public class SlangToWgslTests
{
    /// <summary>
    /// Test compiling a Slang shader source code to WGSL.
    /// </summary>
    [Fact]
    public void TestCompileSlangToWgsl()
    {
        // Arrange
        ShaderCompiler compiler = new ShaderCompiler();
        string slangSourceCode = File.ReadAllText("Data/sprite.slang");
        // Act
        CompileResult result = compiler.CompileSlangToWgsl(slangSourceCode, [ShaderStage.VERTEX, ShaderStage.FRAGMENT], ["main_vs", "main_fs"]);
        Assert.True(result.Success);
        Assert.Contains("main_vs", result.SourceCode);
        Assert.Contains("main_fs", result.SourceCode);
    }

    /// <summary>
    /// Test compiling a Slang shader source code to WGSL.
    /// </summary>
    [Fact]
    public void TestCompileSlangToWgsl2()
    {
        // Arrange
        ShaderCompiler compiler = new ShaderCompiler();
        string slangSourceCode = File.ReadAllText("Data/sprite.slang");
        // Act
        CompileResult result = compiler.CompileSlangToWgsl(slangSourceCode, [ShaderStage.VERTEX, ShaderStage.FRAGMENT], []);
        Assert.True(result.Success);
        Assert.Contains("main_vs", result.SourceCode);
        Assert.Contains("main_fs", result.SourceCode);
    }

    /// <summary>
    /// Compiles shaders from a JSON file. 
    /// Tests Slang to Wgsl JSON compilation.
    /// </summary>
    [Fact]
    public void TestCompileWgslJson()
    {
        // Arrange
        ShaderCompiler compiler = new ShaderCompiler();
        string jsonFilePath = "Data/compile_slang_to_wgsl.json";
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
