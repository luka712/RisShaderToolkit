namespace RisShaderToolkit.Slang
{
    /// <summary>
    /// The result of a Slang operation, which can be either success or failure.
    /// </summary>
    public enum SlangResult : int
    {
        // --- Win COM compatible ---

        SLANG_OK = 0,

        SLANG_FAIL = unchecked((int)0x80004005),

        SLANG_E_NOT_IMPLEMENTED = unchecked((int)0x80004001),
        SLANG_E_NO_INTERFACE = unchecked((int)0x80004002),
        SLANG_E_ABORT = unchecked((int)0x80004004),

        SLANG_E_INVALID_HANDLE = unchecked((int)0x80070006),
        SLANG_E_INVALID_ARG = unchecked((int)0x80070057),
        SLANG_E_OUT_OF_MEMORY = unchecked((int)0x8007000E),

        // --- Core facility (0x200) ---

        SLANG_E_BUFFER_TOO_SMALL = unchecked((int)0x82000001),
        SLANG_E_UNINITIALIZED = unchecked((int)0x82000002),
        SLANG_E_PENDING = unchecked((int)0x82000003),
        SLANG_E_CANNOT_OPEN = unchecked((int)0x82000004),
        SLANG_E_NOT_FOUND = unchecked((int)0x82000005),
        SLANG_E_INTERNAL_FAIL = unchecked((int)0x82000006),
        SLANG_E_NOT_AVAILABLE = unchecked((int)0x82000007),
        SLANG_E_TIME_OUT = unchecked((int)0x82000008),
    }

}
