

using Ris.ShaderToolkit.CObjects;
using Ris.ShaderToolkit.Rules;
using System.Runtime.InteropServices;

namespace Ris.ShaderToolkit;

/// <summary>
/// The shader compiler.
/// </summary>
public class Compiler : IDisposable
{
    private const string DLL_NAME = "shader_toolkit_c.dll";

    [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr create_compiler();

    [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
    static extern void free_compiler(IntPtr compiler);

    [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
    static unsafe extern IntPtr compile_slang_to_glsl(
        IntPtr compilerPtr,
        IntPtr inputFilePath,
        GlslProfile glslProfile,
        ShaderStage shaderStage,
        IntPtr entryPoint,
        IntPtr inputRule,
        IntPtr outputRule);

    private readonly IntPtr NativePtr;

    /// <summary>
    /// The constructor for the <see cref="Compiler"/>.
    /// </summary>
    public Compiler()
    {
        NativePtr = create_compiler();
        if (NativePtr == IntPtr.Zero)
        {
            throw new InvalidOperationException("Failed to create compiler.");
        }
    }

    public CompileResult CompileSlangToGlsl(
        string inputFilePath,
        GlslProfile glslProfile,
        ShaderStage shaderStage,
        string entryPoint = "main",
        ReplaceStageInputNameRule? inputNameRule = null,
        ReplaceStageOutputNameRule? outputNameRule = null
        )
    {
        IntPtr inputFilePathPtr = Marshal.StringToHGlobalAnsi(inputFilePath);
        IntPtr entryPointPtr = Marshal.StringToHGlobalAnsi(entryPoint);
        IntPtr inputRulePtr = CReplaceStageInputNameRule.AllocNative(inputNameRule);
        IntPtr outputRulePtr = CReplaceStageOutputNameRule.AllocNative(outputNameRule);
        try
        {
            IntPtr resultPtr = compile_slang_to_glsl(
                NativePtr,
                inputFilePathPtr,
                glslProfile,
                shaderStage,
                entryPointPtr,
                inputRulePtr,
                outputRulePtr);

            if (resultPtr == IntPtr.Zero)
            {
                throw new InvalidOperationException("Compilation failed: No result returned.");
            }

            CCompileResult cCompileResult = Marshal.PtrToStructure<CCompileResult>(resultPtr);

            CompileResult result = new CompileResult
            {
                Success = cCompileResult.Success,
                SourceCode = cCompileResult.Success
                    ? Marshal.PtrToStringAnsi(cCompileResult.SourceCode) ?? string.Empty
                    : null,
                ErrorMessage = cCompileResult.Success
                    ? null
                    : Marshal.PtrToStringAnsi(cCompileResult.ErrorMessage) ?? "Unknown error."
            };
            cCompileResult.Dispose();
            return result;

        }
        finally
        {
            Marshal.FreeHGlobal(inputFilePathPtr);
            Marshal.FreeHGlobal(entryPointPtr);
            CReplaceStageInputNameRule.FreeNative(inputRulePtr);
            CReplaceStageOutputNameRule.FreeNative(outputRulePtr);
        }
    }

    public void Dispose()
    {
        free_compiler(NativePtr);
    }


}
