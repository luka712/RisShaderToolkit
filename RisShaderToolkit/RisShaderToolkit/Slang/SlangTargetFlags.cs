using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RisShaderToolkit.Slang
{
    using System;

    /// <summary>
    /// Flags to control code generation behavior of a compilation target.
    /// </summary>
    [Flags]
    public enum SlangTargetFlags : uint
    {
        /// <summary>
        /// Default value (no flags set).
        /// </summary>
        None = 0,

        /// <summary>
        /// When compiling for a D3D Shader Model 5.1 or higher target, allocate
        /// distinct register spaces for parameter blocks.
        /// @deprecated This behavior is now enabled unconditionally.
        /// </summary>
        ParameterBlocksUseRegisterSpaces = 1 << 4, // Deprecated

        /// <summary>
        /// Generate target code that contains all entrypoints in a single output module.
        /// </summary>
        GenerateWholeProgram = 1 << 8,

        /// <summary>
        /// Dump out the IR between intermediate compilation steps.
        /// </summary>
        DumpIR = 1 << 9,

        /// <summary>
        /// Generate SPIR-V directly rather than via glslang.
        /// @deprecated Use CompilerOption instead.
        /// </summary>
        GenerateSPIRVDirectly = 1 << 10
    }

}
