using CommunityToolkit.Mvvm.ComponentModel;
using Ris.ShaderToolkit;
using System.Collections.Generic;

namespace RisGameFramework.ShaderToolkit.Client.ViewModels;

public partial class MainViewModel : ViewModelBase
{
    private readonly Compiler _compiler = new Compiler();

    [ObservableProperty]
    private string _sourceShaderCode = @"
        void main() 
        {
            gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
        }";

    [ObservableProperty]
    private string _targetShaderCode = "";

    internal List<ProfileType> ProfileTypes { get; } = [
        ProfileType.GLSL,
        ProfileType.SLANG,
        ProfileType.HLSL
    ];

    internal List<GlslProfile> GlslProfiles { get; } = [
        GlslProfile.GLSL_330,
        GlslProfile.GLSL_400,
        GlslProfile.GLSL_410,
        GlslProfile.GLSL_420,
        GlslProfile.GLSL_430,
        GlslProfile.GLSL_450,
        GlslProfile.GLSL_460,
        GlslProfile.GLES_300,
        GlslProfile.GLES_310,
        GlslProfile.GLES_320,
    ];

    internal List<ShaderStage> ShaderStages { get; } = [
        ShaderStage.VERTEX,
        ShaderStage.FRAGMENT,
        ShaderStage.COMPUTE,
    ];

    [ObservableProperty]
    private ProfileType _sourceProfileType = ProfileType.SLANG;

    [ObservableProperty]
    private ProfileType _targetProfileType = ProfileType.GLSL;

    [ObservableProperty]
    private GlslProfile _targetGlslProfile = GlslProfile.GLES_300;

    [ObservableProperty]
    private ShaderStage _targetShaderStage = ShaderStage.VERTEX;

    public MainViewModel()
    {

    }

    public void Build()
    {
        CompileResult? compileResult = null;
        if(SourceProfileType == ProfileType.SLANG && TargetProfileType == ProfileType.GLSL)
        {
            compileResult = _compiler.CompileSlangSourceCodeToGlsl(SourceShaderCode, TargetGlslProfile, ShaderStage.VERTEX, "main_vs");
        }

        if (compileResult?.Success == true)
        {
            TargetShaderCode = compileResult.SourceCode!;
        }
    }

    partial void OnSourceShaderCodeChanged(string value)
    {
        Build();
    }
}
