using CommunityToolkit.Mvvm.ComponentModel;

namespace RisGameFramework.ShaderToolkit.Client.ViewModels;

/// <summary>
/// The editor view model.
/// </summary>
public partial class EditorViewModel : ObservableObject
{
    [ObservableProperty]
    private string _shaderCode = @"
        void main() 
        {
            gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
        }";
}
