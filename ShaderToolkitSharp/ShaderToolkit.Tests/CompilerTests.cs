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
}
