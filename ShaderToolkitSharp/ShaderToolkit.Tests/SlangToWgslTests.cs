using Ris.ShaderToolkit;

namespace RisShaderToolkit.Tests
{
    /// <summary>
    /// Tests for compiling Slang shaders to WGSL.
    /// </summary>
    public class SlangToWgslTests
    {
        /// <summary>
        /// Test compiling a Slang shader to WGSL.
        /// </summary>
        [Fact]
        public void TestCompileSlangToWgsl()
        {
            // Arrange
            Compiler compiler = new Compiler();
            string inputFilePath = "Data/sprite.slang";
            ShaderStage[] shaderStages = [ShaderStage.VERTEX, ShaderStage.FRAGMENT];
            // Act
            CompileResult result = compiler.CompileSlangToWgsl(inputFilePath, shaderStages, []);
            Assert.True(result.Success);
        }

        /// <summary>
        /// Test compiling a Slang shader source code to WGSL.
        /// </summary>
        [Fact]
        public void TestCompileSourceCodeSlangToWgsl()
        {
            // Arrange
            Compiler compiler = new Compiler();
            string slangSourceCode = File.ReadAllText("Data/sprite.slang");
            // Act
            CompileResult result = compiler.CompileSlangSourceCodeToWgsl(slangSourceCode, [ShaderStage.VERTEX, ShaderStage.FRAGMENT], []);
            Assert.True(result.Success);
        }

        /// <summary>
        /// Compiles shaders from a JSON file. 
        /// Tests Slang to Wgsl JSON compilation.
        /// </summary>
        [Fact]
        public void TestCompileWgslJson()
        {
            // Arrange
            Compiler compiler = new Compiler();
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
}
