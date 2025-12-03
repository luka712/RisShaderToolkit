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
        ShaderStage shaderStage = ShaderStage.Vertex;
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
        ShaderStage shaderStage = ShaderStage.Fragment;
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
        ShaderStage shaderStage = ShaderStage.Vertex;
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
        ShaderStage shaderStage = ShaderStage.Vertex;
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
}
