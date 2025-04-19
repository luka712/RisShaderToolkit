using CommunityToolkit.Mvvm.ComponentModel;

namespace ShaderToolkitSharp.UI.ViewModels;

/// <summary>
/// The view model for the source code editor.
/// </summary>
public partial class SourceCodeEditorViewModel : ViewModelBase
{
    [ObservableProperty]
    public string _sourceCode = "";
}
