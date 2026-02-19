//using RisShaderToolkit;

//namespace ShaderToolkit.Tests;

//public class CompilerTests
//{
//    [Fact]
//    public void TestCreateCompiler()
//    {
//        // Arrange & Act
//        ShaderCompiler compiler = new ShaderCompiler();
//        // If we reach this point, the compiler was created successfully.
//        Assert.True(true);
//    }

//    [Fact]
//    public void TestCompileVertexSlangToGlsl()
//    {
//        // Arrange
//        ShaderCompiler compiler = new ShaderCompiler();
//        string inputFilePath = "Data/sprite.slang";
//        GlslProfile glslProfile = GlslProfile.GLES_300;
//        ShaderStage shaderStage = ShaderStage.VERTEX;
//        string entryPoint = "main_vs";
//        // Act
//        CompileResult result = compiler.CompileSlangToGlsl(inputFilePath, glslProfile, shaderStage, entryPoint);
//        Assert.True(result.Success);
//    }

//    [Fact]
//    public void TestCompileFragmentSlangToGlsl()
//    {
//        // Arrange
//        ShaderCompiler compiler = new ShaderCompiler();
//        string inputFilePath = "Data/sprite.slang";
//        GlslProfile glslProfile = GlslProfile.GLES_300;
//        ShaderStage shaderStage = ShaderStage.FRAGMENT;
//        string entryPoint = "main_fs";
//        // Act
//        CompileResult result = compiler.CompileSlangToGlsl(inputFilePath, glslProfile, shaderStage, entryPoint);
//        Assert.True(result.Success);
//    }

//    [Fact]
//    public void TestCompileVertexSlangToGlsl_InputRule()
//    {
//        // Arrange
//        ShaderCompiler compiler = new ShaderCompiler();
//        string inputFilePath = "Data/sprite.slang";
//        GlslProfile glslProfile = GlslProfile.GLES_300;
//        ShaderStage shaderStage = ShaderStage.VERTEX;
//        string entryPoint = "main_vs";
//        // Act
//        CompileResult result = compiler.CompileSlangToGlsl(inputFilePath, glslProfile, shaderStage, entryPoint,
//            new()
//            {
//                Prefix = "a_"
//            });
//        Assert.True(result.Success);
//    }

//    [Fact]
//    public void TestCompileVertexSlangToGlsl_InputOutputRule()
//    {
//        // Arrange
//        ShaderCompiler compiler = new ShaderCompiler();
//        string inputFilePath = "Data/sprite.slang";
//        GlslProfile glslProfile = GlslProfile.GLES_300;
//        ShaderStage shaderStage = ShaderStage.VERTEX;
//        string entryPoint = "main_vs";
//        // Act
//        CompileResult result = compiler.CompileSlangToGlsl(inputFilePath, glslProfile, shaderStage, entryPoint,
//            new()
//            {
//                Prefix = "a_"
//            },
//            new ()
//            {
//                Prefix = "v_",
//                TrimEntryPointName = true
//            }
//            );
//        Assert.True(result.Success);
//    }

//    /// <summary>
//    /// Compiles shaders from a JSON file.
//    /// </summary>
//    [Fact]
//    public void CompileFromJson_Test()
//    {
//        // Arrange
//        ShaderCompiler compiler = new ShaderCompiler();
//        string jsonFilePath = "Data/compile.json";
//        // Act
//        compiler.CompileFromJson(jsonFilePath);
//        // If we reach this point, the compilation was successful.
//        Assert.True(true);
//        foreach(var result in compiler.CompileFromJson(jsonFilePath).Results)
//        {
//            Assert.True(result.Success);
//        }
//    }

//    /// <summary>
//    /// Compile from source code.
//    /// </summary>
//    [Fact]
//    public void TestCompileSourceCodeSlangToGlsl()
//    {
//        // Arrange
//        ShaderCompiler compiler = new ShaderCompiler();
//        string slangSourceCode = File.ReadAllText("Data/sprite.slang");
//        GlslProfile glslProfile = GlslProfile.GLES_300;
//        ShaderStage shaderStage = ShaderStage.VERTEX;
//        string entryPoint = "main_vs";
//        // Act
//        CompileResult result = compiler.CompileSlangSourceCodeToGlsl(slangSourceCode, glslProfile, shaderStage, entryPoint);
//        Assert.True(result.Success);
//    }

//}
