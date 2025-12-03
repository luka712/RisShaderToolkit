using Ris.ShaderToolkit.Rules;
using System.Runtime.InteropServices;

namespace Ris.ShaderToolkit.CObjects;

/// <summary>
/// The replace stage input name rule from the C/C++ library.
/// </summary>
[StructLayout(LayoutKind.Sequential)]
internal struct CReplaceStageInputNameRule 
{
    /// <summary>
    /// The prefix to add to the stage input names.
    /// </summary>
    public IntPtr Prefix { get; set; }

    /// <summary>
    /// Allocates native memory for the given rule.
    /// </summary>
    /// <param name="rule">The <see cref="ReplaceStageInputNameRule"/> or <c>null</c>.</param>
    /// <returns>The native ptr.</returns>
    internal static IntPtr AllocNative(ReplaceStageInputNameRule? rule)
    {
        IntPtr ptr = IntPtr.Zero;
        if (rule != null)
        {
            CReplaceStageInputNameRule nativeRule = new()
            {
                Prefix = Marshal.StringToHGlobalAnsi(rule.Prefix)
            };

            ptr = Marshal.AllocHGlobal(Marshal.SizeOf<CReplaceStageInputNameRule>());
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
            CReplaceStageInputNameRule nativeRule = Marshal.PtrToStructure<CReplaceStageInputNameRule>(nativePtr);
            Marshal.FreeHGlobal(nativeRule.Prefix);
            Marshal.FreeHGlobal(nativePtr);
        }
    }
}
