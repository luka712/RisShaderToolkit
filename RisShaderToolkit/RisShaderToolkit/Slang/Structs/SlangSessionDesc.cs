using RisShaderToolkit.Slang.Enums;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;


namespace RisShaderToolkit.Slang.Structs
{

    /// <summary>
    /// The description of a Slang session, which is used to configure the session when it is created.
    /// </summary>
    public struct SlangSessionDescription
    {
        /// <summary>
        /// The constructor.
        /// </summary>
        public SlangSessionDescription()
        {
            Targets = new List<SlangTargetDescription>();
            DefaultMatrixLayoutMode = SlangMatrixLayoutMode.RowMajor;
        }

        /// <summary>
        /// Targets to compile for.
        /// The session will be configured to support all of the specified targets, and any entry points compiled in the session will be compiled for all of the specified targets.
        /// </summary>
        public List<SlangTargetDescription> Targets { get; set; }

        /// <summary>
        /// Target flags to use for the session. These flags will be applied to all targets in the session.
        /// </summary>
        public SlangMatrixLayoutMode DefaultMatrixLayoutMode { get; set; }
    }

    [StructLayout(LayoutKind.Sequential)]
    internal unsafe struct SlangSessionDesc
    {
        public UIntPtr structureSize;   // size_t

        public SlangTargetDesc* Targets;          // TargetDesc*
        public long TargetCount;        // SlangInt (usually int64)

        public SlangSessionFlags flags;      // must match underlying type
        public SlangMatrixLayoutMode DefaultMatrixLayoutMode;

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
