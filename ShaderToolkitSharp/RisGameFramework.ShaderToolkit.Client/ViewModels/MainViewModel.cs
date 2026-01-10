using AvaloniaEdit;
using CommunityToolkit.Mvvm.ComponentModel;
using Ris.ShaderToolkit;
using System;

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

    public MainViewModel()
    {

    }

    partial void OnSourceShaderCodeChanged(string value)
    {
       var result = _compiler.CompileSlangSourceCodeToGlsl(value, GlslProfile.GLES_300, ShaderStage.VERTEX, "main_vs");
        if (result != null && result.Success)
        {
            TargetShaderCode = result.SourceCode!;
        }
    }
}
