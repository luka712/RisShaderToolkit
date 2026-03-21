

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
    static unsafe extern IntPtr compile_slang_to_wgsl_ext(
      IntPtr compilerPtr,
      IntPtr sourceCode,
      ShaderStage* shaderStages,
      uint shaderStagesCount,
      IntPtr* entryPoints,
      uint entryPointsCount);

    [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
    static unsafe extern IntPtr compile_slang_to_wgsl(
      IntPtr compilerPtr,
      IntPtr sourceCode,
      ShaderStage* shaderStages,
      uint shaderStagesCount);

    [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
    static unsafe extern IntPtr compile_slang_to_spirv_ext(
      IntPtr compilerPtr,
      IntPtr sourceCode,
      ShaderStage* shaderStages,
      uint shaderStagesCount,
      IntPtr* entryPoints,
      uint entryPointsCount,
      SpirVProfile spirVProfile
      );

    [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
    static unsafe extern IntPtr compile_slang_to_spirv(
    IntPtr compilerPtr,
    IntPtr sourceCode,
    ShaderStage* shaderStages,
    uint shaderStagesCount,
    SpirVProfile spirVProfile
    );

    [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
    static unsafe extern IntPtr compile_slang_to_glsl_ext(
     IntPtr compilerPtr,
     IntPtr sourceCode,
     ShaderStage shaderStage,
     IntPtr entryPoint,
     GlslProfile glslProfile
     );
    
    [DllImport(DLL_NAME, CallingConvention = CallingConvention.Cdecl)]
    static unsafe extern IntPtr compile_slang_to_glsl(
        IntPtr compilerPtr,
        IntPtr sourceCode,
        ShaderStage shaderStage,
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

    private void WriteGlslShaderToFile(ShaderCompileTaskDto task, CompileResult result, GlslProfile glslProfile, ShaderStage stage)
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
            outputFilePath = $"{name}_{_shortStageName[stage]}_{glslProfile.ToString().ToLower()}.glsl";
        }

        if (result.Success && result.SourceCode != null)
        {
            File.WriteAllText(outputFilePath, result.SourceCode);
        }
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
        if (ProfileResolver.IsSpirVProfile(compileTask.Profile, out SpirVProfile spirVProfile))
        {
            string sourceCode = File.ReadAllText(compileTask.InputFilePath);

            var result = CompileSlangToSpirV(
                sourceCode,
                compileTask.Stages.ToArray(),
                spirVProfile,
                compileTask?.EntryPoints
                );
            results.Add(result);

            WriteSpirVShaderToFile(compileTask, result);

            return true;
        }

        return false;
    }

    private bool HandleGlslProfile(List<CompileResult> results, ShaderCompileTaskDto compileTask)
    {
        if (ProfileResolver.IsGlslProfile(compileTask.Profile, out GlslProfile glslProfile))
        {
            string sourceCode = File.ReadAllText(compileTask.InputFilePath);
            foreach (ShaderStage shaderStage in compileTask.Stages)
            {
                var result = CompileSlangToGlsl(
                    sourceCode,
                    shaderStage,
                    glslProfile,
                    compileTask?.EntryPoints != null && compileTask.EntryPoints.Length > 0 ? compileTask.EntryPoints[0] : null
                    );
                results.Add(result);
                WriteGlslShaderToFile(compileTask, result, glslProfile, shaderStage);
            }
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
            else if (HandleGlslProfile(results, compileTask))
            {
                continue;
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

            // Generate default entry points if not provided
            if (entryPoints == null || entryPoints.Length == 0)
            {
                entryPoints = new string[shaderStages.Length];
                for (int i = 0; i < shaderStages.Length; i++)
                {
                    entryPoints[i] = $"main_{_shortStageName[shaderStages[i]]}";
                }
            }

            try
            {
                IntPtr resultPtr = IntPtr.Zero;
                var entryPointsCount = entryPoints.Length;
                IntPtr* entryPointsPtr = stackalloc IntPtr[entryPointsCount];
                for (int i = 0; i < entryPointsCount; i++)
                {
                    entryPointsPtr[i] = Marshal.StringToHGlobalAnsi(entryPoints[i]);
                }

                resultPtr = compile_slang_to_wgsl_ext(
                   NativePtr,
                   slangSourceCodePtr,
                   shaderStagesPtr, (uint)shaderStages.Length,
                   entryPointsPtr, (uint)entryPointsCount);

                for (int i = 0; i < entryPointsCount; i++)
                {
                    Marshal.FreeHGlobal(entryPointsPtr[i]);
                }

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
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                return new CompileResult
                {
                    Success = false,
                    ErrorMessage = $"An error occurred during compilation: {ex.Message}",
                    EntryPoints = entryPoints.ToArray(),
                    ShaderStages = shaderStages
                };
            }
            finally
            {
                Marshal.FreeHGlobal(slangSourceCodePtr);
            }
        }
    }

    /// <summary>
    /// Compiles the given Slang shader to WGSL.
    /// </summary>
    /// <param name="slangSourceCode">The slang source code.</param>
    /// <param name="shaderStages">The <see cref="ShaderStage"/>s to compile.</param>
    /// <param name="spirVProfile">The optional <see cref="SpirVProfile"/>. Default is SPIRV_1_2.</param>
    /// <param name="entryPoints">The optional entry points.</param>
    /// <returns>The <see cref="CompileResult"/>.</returns>
    public CompileResult CompileSlangToSpirV(
        string slangSourceCode,
        ShaderStage[] shaderStages,
        SpirVProfile spirVProfile = SpirVProfile.SPIRV_1_2,
        params string[] entryPoints
        )
    {
        entryPoints = entryPoints ?? Array.Empty<string>();

        IntPtr slangSourceCodePtr = Marshal.StringToHGlobalAnsi(slangSourceCode);

        CCompileResult compileResult = default;
        unsafe
        {
            ShaderStage* shaderStagesPtr = stackalloc ShaderStage[shaderStages.Length];
            for (int i = 0; i < shaderStages.Length; i++)
            {
                shaderStagesPtr[i] = shaderStages[i];
            }

            try
            {
                IntPtr resultPtr;

                if (entryPoints.Length > 0)
                {
                    int entryPointsCount = entryPoints.Length;
                    IntPtr* entryPointsPtr = stackalloc IntPtr[entryPointsCount];
                    for (int i = 0; i < entryPointsCount; i++)
                    {
                        entryPointsPtr[i] = Marshal.StringToHGlobalAnsi(entryPoints[i]);
                    }

                    resultPtr = compile_slang_to_spirv_ext(
                        NativePtr,
                        slangSourceCodePtr,
                        shaderStagesPtr,
                        (uint)shaderStages.Length,
                        entryPointsPtr,
                        (uint)entryPoints.Length,
                        spirVProfile);

                    for (int i = 0; i < entryPoints.Length; i++)
                    {
                        Marshal.FreeHGlobal(entryPointsPtr[i]);
                    }
                }
                else
                {
                    // If no entry points are provided, pass null pointers and zero count
                    resultPtr = compile_slang_to_spirv(
                        NativePtr,
                        slangSourceCodePtr,
                        shaderStagesPtr,
                        (uint)shaderStages.Length,
                        spirVProfile);
                }

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
            try
            {
                IntPtr resultPtr;
                if (!String.IsNullOrEmpty(entryPoint))
                {
                    var entryPointPtr = Marshal.StringToHGlobalAnsi(entryPoint);
                    
                    resultPtr = compile_slang_to_glsl_ext(
                        NativePtr,
                        slangSourceCodePtr,
                        shaderStage,
                        entryPointPtr,
                        glslProfile);
                    
                    Marshal.FreeHGlobal(entryPointPtr);
                }
                else
                {
                    resultPtr = compile_slang_to_glsl(
                        NativePtr,
                        slangSourceCodePtr,
                        shaderStage,
                        glslProfile);
                }

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
            catch (Exception ex)
            {
                return new CompileResult
                {
                    Success = false,
                    ErrorMessage = $"An error occurred during compilation: {ex.Message}",
                    EntryPoints = !string.IsNullOrEmpty(entryPoint) ? [entryPoint] : Array.Empty<string>(),
                    ShaderStages = [shaderStage],
                };
            }
            finally
            {
                Marshal.FreeHGlobal(slangSourceCodePtr);
            }
        }
    }

    public void Dispose()
    {
        free_compiler(NativePtr);
    }
}
