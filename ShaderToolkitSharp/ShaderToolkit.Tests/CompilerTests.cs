using Ris.ShaderToolkit;

namespace ShaderToolkit.Tests;

public class CompilerTests
{
    [Fact]
    public void TestCreateCompiler()
    {
        // Arrange & Act
        Compiler compiler = new Compiler();
        // If we reach this point, the compiler was created successfully.
        Assert.True(true);
    }

    [Fact]
    public void TestCompileVertexSlangToGlsl()
    {
        // Arrange
        Compiler compiler = new Compiler();
        string inputFilePath = "Data/sprite.slang";
        GlslProfile glslProfile = GlslProfile.GLES_300;
        ShaderStage shaderStage = ShaderStage.VERTEX;
        string entryPoint = "main_vs";
        // Act
        CompileResult result = compiler.CompileSlangToGlsl(inputFilePath, glslProfile, shaderStage, entryPoint);
        Assert.True(result.Success);
    }

    [Fact]
    public void TestCompileFragmentSlangToGlsl()
    {
        // Arrange
        Compiler compiler = new Compiler();
        string inputFilePath = "Data/sprite.slang";
        GlslProfile glslProfile = GlslProfile.GLES_300;
        ShaderStage shaderStage = ShaderStage.FRAGMENT;
        string entryPoint = "main_fs";
        // Act
        CompileResult result = compiler.CompileSlangToGlsl(inputFilePath, glslProfile, shaderStage, entryPoint);
        Assert.True(result.Success);
    }

    [Fact]
    public void TestCompileVertexSlangToGlsl_InputRule()
    {
        // Arrange
        Compiler compiler = new Compiler();
        string inputFilePath = "Data/sprite.slang";
        GlslProfile glslProfile = GlslProfile.GLES_300;
        ShaderStage shaderStage = ShaderStage.VERTEX;
        string entryPoint = "main_vs";
        // Act
        CompileResult result = compiler.CompileSlangToGlsl(inputFilePath, glslProfile, shaderStage, entryPoint,
            new()
            {
                Prefix = "a_"
            });
        Assert.True(result.Success);
    }

    [Fact]
    public void TestCompileVertexSlangToGlsl_InputOutputRule()
    {
        // Arrange
        Compiler compiler = new Compiler();
        string inputFilePath = "Data/sprite.slang";
        GlslProfile glslProfile = GlslProfile.GLES_300;
        ShaderStage shaderStage = ShaderStage.VERTEX;
        string entryPoint = "main_vs";
        // Act
        CompileResult result = compiler.CompileSlangToGlsl(inputFilePath, glslProfile, shaderStage, entryPoint,
            new()
            {
                Prefix = "a_"
            },
            new ()
            {
                Prefix = "v_",
                TrimEntryPointName = true
            }
            );
        Assert.True(result.Success);
    }

    /// <summary>
    /// Compiles shaders from a JSON file.
    /// </summary>
    [Fact]
    public void CompileFromJson_Test()
    {
        // Arrange
        Compiler compiler = new Compiler();
        string jsonFilePath = "Data/compile.json";
        // Act
        compiler.CompileFromJson(jsonFilePath);
        // If we reach this point, the compilation was successful.
        Assert.True(true);
        foreach(var result in compiler.CompileFromJson(jsonFilePath).Results)
        {
            Assert.True(result.Success);
        }
    }
}
