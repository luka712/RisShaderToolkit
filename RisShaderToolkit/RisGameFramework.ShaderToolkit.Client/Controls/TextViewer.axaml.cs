using Avalonia;
using Avalonia.Controls;
using Avalonia.Reactive;
using AvaloniaEdit.TextMate;
using System;
using TextMateSharp.Grammars;
using static AvaloniaEdit.TextMate.TextMate;

namespace RisGameFramework.ShaderToolkit.Client.Controls;

/// <summary>
/// The component which is created to view compiled shader content.
/// </summary>
public partial class TextViewer : UserControl
{
    private const string HLSL_GRAMMAR_EXTENSION = ".hlsl";

    private RegistryOptions _registryOptions;
    private Installation _textMateInstallation;

    /// <summary>
    /// The constructor.
    /// </summary>
    public TextViewer()
    {
        InitializeComponent();

        // Setup TextMate with a VS Code-like dark theme
        _registryOptions = new RegistryOptions(ThemeName.DarkPlus);
        _textMateInstallation = ShaderViewerInstance.InstallTextMate(_registryOptions);
        Language language = _registryOptions.GetLanguageByExtension(HLSL_GRAMMAR_EXTENSION);
        _textMateInstallation.SetGrammar(_registryOptions.GetScopeByLanguageId(_registryOptions.GetLanguageByExtension(HLSL_GRAMMAR_EXTENSION).Id));


        IObserver<AvaloniaPropertyChangedEventArgs<string>> observer = new AnonymousObserver<AvaloniaPropertyChangedEventArgs<string>>(args =>
        {
            ShaderViewerInstance.Text = args.NewValue.Value;
        });
        TextProperty.Changed.Subscribe(observer);
    }

    /// <summary>
    /// Invoked whenever source text is changed.
    /// </summary>
    public event EventHandler SourceChanged;

    /// <summary>
    /// The compiled shader text property.
    /// </summary>
    public static readonly StyledProperty<string> TextProperty = AvaloniaProperty.Register<Editor, string>(nameof(Text), "");

    /// <summary>
    /// The compiled shader text.
    /// </summary>
    public string Text
    {
        get
        {
            return GetValue(TextProperty);
        }
        set
        {
            SetValue(TextProperty, value);
            ShaderViewerInstance?.Text = value;
        }
    }
}