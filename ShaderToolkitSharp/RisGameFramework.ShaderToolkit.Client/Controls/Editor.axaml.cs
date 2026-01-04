using Avalonia;
using Avalonia.Controls;
using Avalonia.Markup.Xaml;
using AvaloniaEdit.TextMate;
using RisGameFramework.ShaderToolkit.Client.ViewModels;
using TextMateSharp.Grammars;
using static AvaloniaEdit.TextMate.TextMate;

namespace RisGameFramework.ShaderToolkit.Client.Controls;

/// <summary>
/// The shader editor control.
/// </summary>
public partial class Editor : UserControl
{
    private const string HLSL_GRAMMAR_EXTENSION = ".hlsl";

    private EditorViewModel _viewModel = new();
    private RegistryOptions _registryOptions;
    private Installation _textMateInstallation;

    /// <summary>
    /// The constructor.
    /// </summary>
    public Editor()
    {
        InitializeComponent();

        // Setup TextMate with a VS Code-like dark theme
        _registryOptions = new RegistryOptions(ThemeName.DarkPlus);
        _textMateInstallation = ShaderEditorInstance.InstallTextMate(_registryOptions);
        Language language = _registryOptions.GetLanguageByExtension(HLSL_GRAMMAR_EXTENSION);
        _textMateInstallation.SetGrammar(_registryOptions.GetScopeByLanguageId(_registryOptions.GetLanguageByExtension(HLSL_GRAMMAR_EXTENSION).Id));

        DataContext = _viewModel;
        ShaderEditorInstance.Text = _viewModel.ShaderCode;
    }
}