
namespace Ris.ShaderToolkit;

/// <summary>
/// The aggregated compile result.
/// </summary>
/// <param name="compileResults">The compile results.</param>
public class AggregatedCompileResult(IReadOnlyList<CompileResult> compileResults)
{
    /// <summary>
    /// The compile results.
    /// </summary>
    public IReadOnlyList<CompileResult> Results => compileResults;
}
