using Ris.ShaderToolkit.Rules;
using System.Runtime.InteropServices;

namespace Ris.ShaderToolkit.CObjects;

/// <summary>
/// The replace stage input name rule from the C/C++ library.
/// </summary>
[StructLayout(LayoutKind.Sequential)]
internal struct CReplaceStageOutputNameRule 
{
    /// <summary>
    /// The prefix to add to the stage input names.
    /// </summary>
    public IntPtr Prefix { get; set; }

    /// <summary>
    /// Sets whether to trim the entry point name from output variable names.
    /// </summary>
    public bool TrimEntryPointName { get; set; }

    /// <summary>
    /// Allocates native memory for the given rule.
    /// </summary>
    /// <param name="rule">The <see cref="ReplaceStageOutputNameRule"/> or <c>null</c>.</param>
    /// <returns>The native ptr.</returns>
    internal static IntPtr AllocNative(ReplaceStageOutputNameRule? rule)
    {
        IntPtr ptr = IntPtr.Zero;
        if (rule != null)
        {
            CReplaceStageOutputNameRule nativeRule = new()
            {
                Prefix = Marshal.StringToHGlobalAnsi(rule.Prefix),
                TrimEntryPointName = rule.TrimEntryPointName
            };

            ptr = Marshal.AllocHGlobal(Marshal.SizeOf<CReplaceStageOutputNameRule>());
            Marshal.StructureToPtr(nativeRule, ptr, false);
        }
        return ptr;
    }

    /// <summary>
    /// Frees the native memory allocated for the rule.
    /// </summary>
    /// <param name="nativePtr">The native pointer.</param>
    internal static void FreeNative(IntPtr nativePtr)
    {
        if (nativePtr != IntPtr.Zero)
        {
            CReplaceStageOutputNameRule nativeRule = Marshal.PtrToStructure<CReplaceStageOutputNameRule>(nativePtr);
            Marshal.FreeHGlobal(nativeRule.Prefix);
            Marshal.FreeHGlobal(nativePtr);
        }
    }
}
