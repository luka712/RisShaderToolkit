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
        CompileResult result = compiler.CompileSlangToSpirV(slangSourceCode, 
            [ShaderStage.VERTEX, ShaderStage.FRAGMENT], 
            SpirVProfile.SPIRV_1_2, 
            ["main_vs", "main_fs"]);
        
        Assert.True(result.Success);
        Assert.NotNull(result.BinarySourceCode);
        Assert.True(result.BinarySourceCode.Length > 0);
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
        CompileResult result = compiler.CompileSlangToSpirV(slangSourceCode, [ShaderStage.VERTEX, ShaderStage.FRAGMENT], entryPoints: []);
        Assert.True(result.Success);
        Assert.NotNull(result.BinarySourceCode);
        Assert.True(result.BinarySourceCode.Length > 0);
    }

    /// <summary>
    /// Compiles shaders from a JSON file. 
    /// Tests Slang to SpirV JSON compilation.
    /// </summary>
    [Fact]
    public void TestCompilSpirVJson()
    {
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
