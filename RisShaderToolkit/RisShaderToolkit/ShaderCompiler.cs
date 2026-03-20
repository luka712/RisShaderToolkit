

using RisShaderToolkit.CObjects;
using RisShaderToolkit.Dto;
using System.Runtime.InteropServices;

namespace RisShaderToolkit;

/// <summary>
/// The shader compiler.
/// </summary>
public class ShaderCompiler : IDisposable
{
    private const string DLL_NAME = "shader_toolkit_c";

    [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
    static extern IntPtr create_compiler();

    [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
    static extern void free_compiler(IntPtr compiler);

    [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
    static unsafe extern IntPtr compile_slang_to_wgsl(
      IntPtr compilerPtr,
      IntPtr sourceCode,
      ShaderStage* shaderStages,
      uint shaderStagesCount,
      IntPtr* entryPoints,
      uint entryPointsCount);

    [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
    static unsafe extern IntPtr compile_slang_to_spirv(
      IntPtr compilerPtr,
      IntPtr sourceCode,
      ShaderStage shaderStage,
      IntPtr entryPoint,
      SpirVProfile spirVProfile
      );

    [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
    static unsafe extern IntPtr compile_slang_to_glsl(
     IntPtr compilerPtr,
     IntPtr sourceCode,
     ShaderStage shaderStage,
     IntPtr entryPoint,
     GlslProfile glslProfile
     );

    private readonly IntPtr NativePtr;
    private readonly JsonReader _jsonReader = new();

    private Dictionary<ShaderStage, string> _shortStageName = new()
    {
        [ShaderStage.VERTEX] = "vs",
        [ShaderStage.FRAGMENT] = "fs",
        [ShaderStage.COMPUTE] = "cs",
    };


    /// <summary>
    /// The constructor for the <see cref="ShaderCompiler"/>.
    /// </summary>
    public ShaderCompiler()
    {
        NativeResolver.Setup();
        NativePtr = create_compiler();
        if (NativePtr == IntPtr.Zero)
        {
            throw new InvalidOperationException("Failed to create compiler.");
        }
    }

    private void WriteGlslShaderToFile(ShaderCompileTaskDto task, CompileResult result, GlslProfile glslProfile)
    {
        throw new InvalidOperationException("hello");

        //if (!result.Success)
        //{
        //    return;
        //}

        //string? outputFilePath = task.OutputFilePath;
        //if (string.IsNullOrEmpty(outputFilePath))
        //{
        //    string[] split = task.InputFilePath.Split('.');
        //    split = split[..^1]; // Remove extension

        //    string name = String.Join("", split);
        //    outputFilePath = $"{name}_{_shortStageName[task.Stage.Value]}_{glslProfile.ToString().ToLower()}.glsl";
        //}

        //if (result.Success && result.SourceCode != null)
        //{
        //    File.WriteAllText(outputFilePath, result.SourceCode);
        //}
    }

    private void WriteWgslShaderToFile(ShaderCompileTaskDto task, CompileResult result)
    {
        if (!result.Success)
        {
            return;
        }
        string? outputFilePath = task.OutputFilePath;
        if (string.IsNullOrEmpty(outputFilePath))
        {
            string[] split = task.InputFilePath.Split('.');
            split = split[..^1]; // Remove extension
            string name = String.Join("", split);
            outputFilePath = $"{name}.wgsl";
        }
        if (result.Success && result.SourceCode != null)
        {
            File.WriteAllText(outputFilePath, result.SourceCode);
        }
    }

    private void WriteSpirVShaderToFile(ShaderCompileTaskDto task, CompileResult result)
    {
        if (!result.Success)
        {
            return;
        }
        string? outputFilePath = task.OutputFilePath;
        if (string.IsNullOrEmpty(outputFilePath))
        {
            string[] split = task.InputFilePath.Split('.');
            split = split[..^1]; // Remove extension
            string name = String.Join("", split);
            outputFilePath = $"{name}.spv";
        }
        if (result.Success && result.SourceCode != null)
        {
            File.WriteAllText(outputFilePath, result.SourceCode);
        }
    }


    private bool HandleSpirVProfile(List<CompileResult> results, ShaderCompileTaskDto compileTask)
    {
        if (compileTask.Stages == null || compileTask.Stages.Count != 1)
        {
            throw new InvalidOperationException("SPIR-V compilation requires exactly one shader stage.");
        }

        if (ProfileResolver.IsSpirVProfile(compileTask.Profile, out SpirVProfile spirVProfile))
        {
            string sourceCode = File.ReadAllText(compileTask.InputFilePath);

            var result = CompileSlangToSpirV(
                sourceCode,
                compileTask.Stages.FirstOrDefault(),
                spirVProfile,
                compileTask?.EntryPoints?.FirstOrDefault()
                );
            results.Add(result);

            WriteSpirVShaderToFile(compileTask, result);

            return true;
        }

        return false;
    }

    /// <summary>
    /// Compiles shaders based on the given JSON file.
    /// </summary>
    /// <param name="jsonFilePath">The json file path.</param>
    /// <exception cref="InvalidOperationException"></exception>
    public AggregatedCompileResult CompileFromJson(string jsonFilePath)
    {
        IReadOnlyList<ShaderCompileTaskDto> compileTasks = _jsonReader.LoadJson(jsonFilePath);

        List<CompileResult> results = new List<CompileResult>();
        foreach (ShaderCompileTaskDto compileTask in compileTasks)
        {
            if (compileTask.Profile == AnyProfile.WGSL)
            {
                string sourceCode = File.ReadAllText(compileTask.InputFilePath);

                CompileResult result = CompileSlangToWgsl(
                    sourceCode,
                    compileTask.Stages.ToArray(),
                    compileTask.EntryPoints ?? []);
                results.Add(result);

                WriteWgslShaderToFile(compileTask, result);
            }
            else if (HandleSpirVProfile(results, compileTask))
            {
                continue;
            }
            else if (compileTask.SourceProfile == AnyProfile.SLANG && ProfileResolver.IsGlslProfile(compileTask.Profile, out GlslProfile glslProfile))
            {
                //CompileResult result = CompileSlangToGlsl(
                //  compileTask.InputFilePath,
                //  glslProfile,
                //  compileTask.Stage.Value,
                //  compileTask.EntryPoint,
                //  compileTask.InputNameRule,
                //  compileTask.OutputNameRule);

                //results.Add(result);
                //WriteGlslShaderToFile(compileTask, result, glslProfile);
            }
            else
            {
                throw new InvalidOperationException(
                    $"Unsupported profile conversion from {compileTask.SourceProfile} to {compileTask.Profile}.");
            }
        }

        return new(results);
    }

    /// <summary>
    /// Compiles the given Slang shader to WGSL.
    /// </summary>
    /// <param name="slangSourceCode">The slang source code.</param>
    /// <param name="shaderStages">The <see cref="ShaderStage"/>'s to compile.</param>
    /// <param name="entryPoints">The optional entry points.</param>
    /// <returns>The <see cref="CompileResult"/>.</returns>
    public CompileResult CompileSlangToWgsl(
        string slangSourceCode,
        ShaderStage[] shaderStages,
        params string[] entryPoints
        )
    {
        IntPtr slangSourceCodePtr = Marshal.StringToHGlobalAnsi(slangSourceCode);

        CCompileResult compileResult = default;
        unsafe
        {
            ShaderStage* shaderStagesPtr = stackalloc ShaderStage[shaderStages.Length];
            for (int i = 0; i < shaderStages.Length; i++)
            {
                shaderStagesPtr[i] = shaderStages[i];
            }

            IntPtr* entryPointsPtr = stackalloc IntPtr[entryPoints.Length];
            for (int i = 0; i < entryPoints.Length; i++)
            {
                entryPointsPtr[i] = Marshal.StringToHGlobalAnsi(entryPoints[i]);
            }

            try
            {
                IntPtr resultPtr = compile_slang_to_wgsl(
                    NativePtr,
                    slangSourceCodePtr,
                    shaderStagesPtr, (uint)shaderStages.Length,
                    entryPointsPtr, (uint)entryPoints.Length);

                if (resultPtr == IntPtr.Zero)
                {
                    throw new InvalidOperationException("Compilation failed: No result returned.");
                }

                compileResult = Marshal.PtrToStructure<CCompileResult>(resultPtr);

                CompileResult result = new CompileResult
                {
                    Success = compileResult.Success,
                    SourceCode = compileResult.Success
                        ? Marshal.PtrToStringAnsi(compileResult.SourceCode) ?? string.Empty
                        : null,
                    ErrorMessage = compileResult.Success
                        ? null
                        : Marshal.PtrToStringAnsi(compileResult.ErrorMessage) ?? "Unknown error.",
                    EntryPoints = entryPoints.ToArray(),
                    ShaderStages = shaderStages
                };
                compileResult.Dispose();
                return result;

            }
            finally
            {
                Marshal.FreeHGlobal(slangSourceCodePtr);
                for (int i = 0; i < entryPoints.Length; i++)
                {
                    Marshal.FreeHGlobal(entryPointsPtr[i]);
                }
            }
        }
    }

    /// <summary>
    /// Compiles the given Slang shader to WGSL.
    /// </summary>
    /// <param name="slangSourceCode">The slang source code.</param>
    /// <param name="shaderStage">The <see cref="ShaderStage"/> to compile.</param>
    /// <param name="spirVProfile">The optional <see cref="SpirVProfile"/>. Default is SPIRV_1_2.</param>
    /// <param name="entryPoint">The optional entry point.</param>
    /// <returns>The <see cref="CompileResult"/>.</returns>
    public CompileResult CompileSlangToSpirV(
        string slangSourceCode,
        ShaderStage shaderStage,
        SpirVProfile spirVProfile = SpirVProfile.SPIRV_1_2,
        string? entryPoint = null
        )
    {
        IntPtr slangSourceCodePtr = Marshal.StringToHGlobalAnsi(slangSourceCode);

        CCompileResult compileResult = default;
        unsafe
        {
            IntPtr entryPointPtr = Marshal.StringToHGlobalAnsi(entryPoint);

            try
            {
                IntPtr resultPtr = compile_slang_to_spirv(
                    NativePtr,
                    slangSourceCodePtr,
                    shaderStage,
                    entryPointPtr,
                    spirVProfile);

                if (resultPtr == IntPtr.Zero)
                {
                    throw new InvalidOperationException("Compilation failed: No result returned.");
                }

                compileResult = Marshal.PtrToStructure<CCompileResult>(resultPtr);

                CompileResult result = new CompileResult
                {
                    Success = compileResult.Success,
                    SourceCode = compileResult.Success
                        ? Marshal.PtrToStringAnsi(compileResult.SourceCode) ?? string.Empty
                        : null,
                    ErrorMessage = compileResult.Success
                        ? null
                        : Marshal.PtrToStringAnsi(compileResult.ErrorMessage) ?? "Unknown error.",
                    EntryPoints = !string.IsNullOrEmpty(entryPoint) ? [entryPoint] : Array.Empty<string>(),
                    ShaderStages = [shaderStage],
                };

                byte[] bytes = new byte[compileResult.BinaryCodeLength];
                for (int i = 0; i < compileResult.BinaryCodeLength; i++)
                {
                    bytes[i] = Marshal.ReadByte(compileResult.BinarySourceCode, i);
                }
                result.BinarySourceCode = bytes;

                compileResult.Dispose();
                return result;

            }
            finally
            {
                Marshal.FreeHGlobal(slangSourceCodePtr);
                Marshal.FreeHGlobal(entryPointPtr);
            }
        }
    }

    /// <summary>
    /// Compiles the given Slang shader to GLSL.
    /// </summary>
    /// <param name="slangSourceCode">The slang source code.</param>
    /// <param name="shaderStage">The <see cref="ShaderStage"/> to compile.</param>
    /// <param name="glslProfile">The optional <see cref="GlslProfile"/>. Default is GLSL_450.</param>
    /// <param name="entryPoint">The optional entry point.</param>
    /// <returns>The <see cref="CompileResult"/>.</returns>
    /// <exception cref="InvalidOperationException"></exception>
    public CompileResult CompileSlangToGlsl(
        string slangSourceCode,
        ShaderStage shaderStage,
        GlslProfile glslProfile = GlslProfile.GLSL_450,
        string? entryPoint = null
        )
    {
        IntPtr slangSourceCodePtr = Marshal.StringToHGlobalAnsi(slangSourceCode);

        CCompileResult compileResult = default;
        unsafe
        {
            IntPtr entryPointPtr = Marshal.StringToHGlobalAnsi(entryPoint);

            try
            {
                IntPtr resultPtr = compile_slang_to_glsl(
                    NativePtr,
                    slangSourceCodePtr,
                    shaderStage,
                    entryPointPtr,
                    glslProfile);

                if (resultPtr == IntPtr.Zero)
                {
                    throw new InvalidOperationException("Compilation failed: No result returned.");
                }

                compileResult = Marshal.PtrToStructure<CCompileResult>(resultPtr);

                CompileResult result = new CompileResult
                {
                    Success = compileResult.Success,
                    SourceCode = compileResult.Success
                        ? Marshal.PtrToStringAnsi(compileResult.SourceCode) ?? string.Empty
                        : null,
                    ErrorMessage = compileResult.Success
                        ? null
                        : Marshal.PtrToStringAnsi(compileResult.ErrorMessage) ?? "Unknown error.",
                    EntryPoints = !string.IsNullOrEmpty(entryPoint) ? [entryPoint] : Array.Empty<string>(),
                    ShaderStages = [shaderStage],
                };

                result.SourceCode = Marshal.PtrToStringAnsi(compileResult.SourceCode);

                compileResult.Dispose();
                return result;

            }
            finally
            {
                Marshal.FreeHGlobal(slangSourceCodePtr);
                Marshal.FreeHGlobal(entryPointPtr);
            }
        }
    }

    public void Dispose()
    {
        free_compiler(NativePtr);
    }
}
