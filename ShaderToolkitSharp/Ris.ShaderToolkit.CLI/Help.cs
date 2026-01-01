using System.Text;

namespace Ris.ShaderToolkit;

// <summary>
/// The help message for the CLI.
/// </summary>
internal static class Help
{
    /// <summary>
    /// Print the help message to the console.
    /// </summary>
    internal static void PrintHelp()
    {
        StringBuilder stringBuilder = new();
        stringBuilder.AppendLine("ris-shader-toolkit-cli - A command line interface for 'RisShaderToolkit'.");
        stringBuilder.AppendLine();
        stringBuilder.AppendLine("Usage:");
        stringBuilder.AppendLine("  ris-shader-toolkit-cli [options]");
        stringBuilder.AppendLine();
        stringBuilder.AppendLine("Options:");
        stringBuilder.AppendLine("  -j, --json <json>             Load from JSON file.");
        stringBuilder.AppendLine("  -h, --help                    Show this help message and exit.");
        Console.WriteLine(stringBuilder.ToString());
    }
}