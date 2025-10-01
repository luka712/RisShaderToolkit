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
    }
}