using RisShaderToolkit.Slang.Enums;
using System.Runtime.InteropServices;

namespace RisShaderToolkit.Slang.Structs
{
    /// <summary>
    /// The description of a compilation target for the Slang compiler.
    /// </summary>
    public struct SlangTargetDescription
    {
        /// <summary>
        /// The constructor, which initializes the structure with default values.
        /// </summary>
        public SlangTargetDescription()
        {
            Format = SlangCompileTarget.SLANG_TARGET_UNKNOWN;
            Profile = SlangProfileID.SLANG_PROFILE_UNKNOWN;
        }

        /// <summary>
        /// The target format to generate code for.
        /// </summary>
        public SlangCompileTarget Format { get; set; } 

        /// <summary>
        /// The profile to target when generating code.
        /// The meaning of this field depends on the value of `Format`, and may be ignored for some formats.
        /// </summary>
        public SlangProfileID Profile { get; set; }

        internal SlangTargetDesc ToCStruct()
        {
            return new SlangTargetDesc
            {
                Format = this.Format,
                Profile = this.Profile
            };
        }
    }


    [StructLayout(LayoutKind.Sequential)]
    internal struct SlangTargetDesc
    {
        /// <summary>
        /// The constructor, which initializes the structure with default values.
        /// </summary>
        public SlangTargetDesc()
        {
            StructureSize = (UIntPtr)Marshal.SizeOf<SlangTargetDesc>();
            Format = SlangCompileTarget.SLANG_TARGET_UNKNOWN;
            Profile = SlangProfileID.SLANG_PROFILE_UNKNOWN;
            Flags = SlangTargetFlags.GenerateSPIRVDirectly;
            FloatingPointMode = SlangFloatingPointMode.Default;
            LineDirectiveMode = SlangLineDirectiveMode.Default;
            ForceGLSLScalarBufferLayout = false;
            CompilerOptionEntries = IntPtr.Zero;
            CompilerOptionEntryCount = 0;
        }

        public UIntPtr StructureSize;
        public SlangCompileTarget Format;
        public SlangProfileID Profile;
        public SlangTargetFlags Flags;
        public SlangFloatingPointMode FloatingPointMode;
        public SlangLineDirectiveMode LineDirectiveMode;

        [MarshalAs(UnmanagedType.I1)]
        public bool ForceGLSLScalarBufferLayout;

        public IntPtr CompilerOptionEntries;
        public uint CompilerOptionEntryCount;
    }

}
