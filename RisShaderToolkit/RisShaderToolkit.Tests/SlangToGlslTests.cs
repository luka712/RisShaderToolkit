namespace RisShaderToolkit.Tests;

/// <summary>
/// Tests for compiling Slang shaders to GLSL.
/// </summary>
public class SlangToGlslTests
{
    /// <summary>
    /// Test compiling a Slang shader source code to GLSL.
    /// </summary>
    [Fact]
    public void TestCompileSlangToGlsl()
    {
        // Arrange
        ShaderCompiler compiler = new ShaderCompiler();
        string slangSourceCode = File.ReadAllText("Data/sprite.slang");
        // Act
        CompileResult vertexResult = compiler.CompileSlangToGlsl(slangSourceCode,
            ShaderStage.VERTEX,
            GlslProfile.GLSL_450,
            "main_vs");

        Assert.True(vertexResult.Success);
        Assert.NotNull(vertexResult.SourceCode);
        Assert.True(vertexResult.SourceCode.Length > 0);
        Assert.Contains("main()", vertexResult.SourceCode);

        // Act
        CompileResult fragmentResult = compiler.CompileSlangToGlsl(slangSourceCode,
            ShaderStage.FRAGMENT,
            GlslProfile.GLSL_450,
            "main_fs");

        Assert.True(fragmentResult.Success);
        Assert.NotNull(fragmentResult.SourceCode);
        Assert.True(fragmentResult.SourceCode.Length > 0);
        Assert.Contains("main()", fragmentResult.SourceCode);
    }

    /// <summary>
    /// Test compiling a Slang shader source code to SPIR-V.
    /// </summary>
    [Fact]
    public void TestCompileSlangToGlsl2()
    {
        // Arrange
        ShaderCompiler compiler = new ShaderCompiler();
        string slangSourceCode = File.ReadAllText("Data/sprite.slang");
        // Act
        CompileResult vertexResult = compiler.CompileSlangToGlsl(slangSourceCode,
            ShaderStage.VERTEX,
            GlslProfile.GLSL_450);

        Assert.True(vertexResult.Success);
        Assert.NotNull(vertexResult.SourceCode);
        Assert.True(vertexResult.SourceCode.Length > 0);
        Assert.Contains("main()", vertexResult.SourceCode);

        // Act
        CompileResult fragmentResult = compiler.CompileSlangToGlsl(slangSourceCode,
            ShaderStage.FRAGMENT,
            GlslProfile.GLSL_450);

        Assert.True(fragmentResult.Success);
        Assert.NotNull(fragmentResult.SourceCode);
        Assert.True(fragmentResult.SourceCode.Length > 0);
        Assert.Contains("main()", fragmentResult.SourceCode);
    }

    /// <summary>
    /// Test compiling a Slang shader source code to GLSL.
    /// </summary>
    [Fact]
    public void TestCompileSlangToGlsl300es()
    {
        // Arrange
        ShaderCompiler compiler = new ShaderCompiler();
        string slangSourceCode = File.ReadAllText("Data/sprite.slang");
        // Act
        CompileResult vertexResult = compiler.CompileSlangToGlsl(slangSourceCode,
            ShaderStage.VERTEX,
            GlslProfile.GLES_300,
            "main_vs");

        Assert.True(vertexResult.Success);
        Assert.NotNull(vertexResult.SourceCode);
        Assert.True(vertexResult.SourceCode.Length > 0);
        Assert.Contains("main()", vertexResult.SourceCode);

        // Act
        CompileResult fragmentResult = compiler.CompileSlangToGlsl(slangSourceCode,
            ShaderStage.FRAGMENT,
            GlslProfile.GLES_300,
            "main_fs");

        Assert.True(fragmentResult.Success);
        Assert.NotNull(fragmentResult.SourceCode);
        Assert.True(fragmentResult.SourceCode.Length > 0);
        Assert.Contains("main()", fragmentResult.SourceCode);
    }


    /// <summary>
    /// Test compiling a Slang shader source code to GLSL.
    /// </summary>
    [Fact]
    public void TestCompileSlangToGlsl300es2()
    {
        // Arrange
        ShaderCompiler compiler = new ShaderCompiler();
        string slangSourceCode = File.ReadAllText("Data/sprite.slang");
        // Act
        CompileResult vertexResult = compiler.CompileSlangToGlsl(slangSourceCode,
            ShaderStage.VERTEX,
            GlslProfile.GLES_300);

        Assert.True(vertexResult.Success);
        Assert.NotNull(vertexResult.SourceCode);
        Assert.True(vertexResult.SourceCode.Length > 0);
        Assert.Contains("main()", vertexResult.SourceCode);

        // Act
        CompileResult fragmentResult = compiler.CompileSlangToGlsl(slangSourceCode,
            ShaderStage.FRAGMENT,
            GlslProfile.GLES_300);

        Assert.True(fragmentResult.Success);
        Assert.NotNull(fragmentResult.SourceCode);
        Assert.True(fragmentResult.SourceCode.Length > 0);
        Assert.Contains("main()", fragmentResult.SourceCode);
    }

    /// <summary>
    /// Compiles shaders from a JSON file. 
    /// Tests Slang to SpirV JSON compilation.
    /// </summary>
    [Fact]
    public void TestCompileGlslJson()
    {
        // Arrange
        ShaderCompiler compiler = new ShaderCompiler();
        string jsonFilePath = "Data/compile_slang_to_glsl.json";
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
