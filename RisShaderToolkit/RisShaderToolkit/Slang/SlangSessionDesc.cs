using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace RisShaderToolkit.Slang
{


    [Flags]
    public enum SlangSessionFlags : uint
    {
        None = 0
    }

    public enum SlangMatrixLayoutMode : uint
    {
        Unknown = 0,
        RowMajor = 1,
        ColumnMajor = 2
    }


    [StructLayout(LayoutKind.Sequential)]
    public struct SlangSessionDesc
    {
        public UIntPtr structureSize;   // size_t

        public IntPtr targets;          // TargetDesc*
        public long targetCount;        // SlangInt (usually int64)

        public SlangSessionFlags flags;      // must match underlying type
        public SlangMatrixLayoutMode defaultMatrixLayoutMode;

        public IntPtr searchPaths;      // char const* const*
        public long searchPathCount;    // SlangInt

        public IntPtr preprocessorMacros;       // PreprocessorMacroDesc*
        public long preprocessorMacroCount;     // SlangInt

        public IntPtr fileSystem;       // ISlangFileSystem*

        [MarshalAs(UnmanagedType.I1)]
        public bool enableEffectAnnotations;

        [MarshalAs(UnmanagedType.I1)]
        public bool allowGLSLSyntax;

        public IntPtr compilerOptionEntries;    // CompilerOptionEntry*
        public uint compilerOptionEntryCount;
    }
}
