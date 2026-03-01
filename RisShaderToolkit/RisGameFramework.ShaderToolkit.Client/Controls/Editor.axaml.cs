using Avalonia;
using Avalonia.Controls;
using AvaloniaEdit.TextMate;
using System;
using TextMateSharp.Grammars;
using static AvaloniaEdit.TextMate.TextMate;

namespace RisGameFramework.ShaderToolkit.Client.Controls;

/// <summary>
/// The shader editor control.
/// </summary>
public partial class Editor : UserControl
{
    private const string HLSL_GRAMMAR_EXTENSION = ".hlsl";

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

        ShaderEditorInstance.TextChanged += (s, e) =>
        {
            SetValue(SourceProperty, ShaderEditorInstance.Text);
            SourceChanged?.Invoke(this, e);
        };
    }

    /// <summary>
    /// Invoked whenever source text is changed.
    /// </summary>
    public event EventHandler SourceChanged;

    /// <summary>
    /// The source property.
    /// </summary>
    public static readonly StyledProperty<string> SourceProperty = AvaloniaProperty.Register<Editor, string>(nameof(Source), "");

    /// <summary>
    /// The source shader text.
    /// </summary>
    public string Source
    {
        get
        {
            return GetValue(SourceProperty);
        }
        set
        {
            SetValue(SourceProperty, value);
            ShaderEditorInstance?.Text = value;
        }
    }
}