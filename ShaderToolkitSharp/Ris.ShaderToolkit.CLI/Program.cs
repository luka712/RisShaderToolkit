
using Ris.ShaderToolkit;

Compiler compiler = new Compiler();

string? json = ArgHelper.GetArgumentValue(args, "--json") ?? ArgHelper.GetArgumentValue(args, "--j") ?? "D:\\Projects\\ShaderToolkitSharp\\ShaderToolkitSharp\\ShaderToolkit.Tests\\Data\\compile.json";

if (json is null)
{
    Help.PrintHelp();
    return;
}

try
{
    AggregatedCompileResult result = compiler.CompileFromJson(json);
    foreach (CompileResult compileResult in result.Results)
    {
        if (compileResult.GlslProfile != null)
        {
            if (compileResult.Success)
            {
                Console.WriteLine($"Compilation of {compileResult.InputFilePath} to {compileResult.GlslProfile} succeeded.");
            }
            else
            {
                Console.WriteLine($"Compilation of {compileResult.InputFilePath} to {compileResult.GlslProfile} failed. {compileResult.ErrorMessage}");
            }
        }
        else
        {
            Console.WriteLine($"Compilation of {compileResult.InputFilePath} failed. {compileResult.ErrorMessage}");
        }
    }
}
catch (Exception ex)
{
    Console.WriteLine($"An error occurred during compilation: {ex.Message}");
}