namespace ShaderToolkit.Tests
{
    [Collection("GlslToGlslTests")]
    public class GlslToGlslTests
    {
        [Fact]
        public void TestCreateCompiler()
        {
            GlslToGlslShaderCCompiler compiler = new GlslToGlslShaderCCompiler();
            Assert.NotEqual(IntPtr.Zero, compiler.NativePtr);
        }

        [Fact]
        public void TestCompileGlslToGlsl()
        {
            GlslToGlslShaderCCompiler compiler = new GlslToGlslShaderCCompiler();
            string sourceCode = "#version 450 core\n void main() { gl_Position = vec4(0.0); }";
            string inGlslProfile = "vs450";
            string outGlslProfile = "vs300es";
            string result = compiler.CompilelslToGlsl(sourceCode, inGlslProfile, outGlslProfile);
            Assert.NotNull(result);
        }
    }
}