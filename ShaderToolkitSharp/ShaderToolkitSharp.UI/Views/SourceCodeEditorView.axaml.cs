using System;
using Avalonia.Controls;

namespace ShaderToolkitSharp.UI.Views;

public partial class SourceCodeEditorView : UserControl
{
    private AvaloniaEdit.TextEditor textEditor;
    private GlslToGlslShaderCCompiler glslToGlslShaderCCompiler = new();

    public SourceCodeEditorView()
    {
        InitializeComponent();

        DataContext = new ViewModels.SourceCodeEditorViewModel();

        textEditor = this.FindControl<AvaloniaEdit.TextEditor>("Editor")!;
        textEditor.TextChanged += TextEditor_TextChanged;
    }

    private void TextEditor_TextChanged(object? sender, EventArgs args)
    {
        // Handle text input events here if needed
        // For example, you can update the ViewModel with the new text
        var viewModel = (ViewModels.SourceCodeEditorViewModel)DataContext;

        bool result = glslToGlslShaderCCompiler.CompilelslToGlsl(textEditor.Text, "vs450", "vs300es",
            out string targetCode, out string errorMessage);
        Console.WriteLine(targetCode);
        Console.WriteLine(errorMessage);
    }
}
