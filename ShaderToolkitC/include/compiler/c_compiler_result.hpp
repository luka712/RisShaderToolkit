#ifndef COMPILER_RESULT_C_H
#define COMPILER_RESULT_C_H

#include "compiler/compile_result.hpp"
#include "macros.hpp"

extern "C" {

    //! The C-compatible structure representing the result of a compilation.
    API_EXPORT
    struct  c_CompileResult {

        //! Indicates whether the compilation was successful.
        bool success;

        //! The compiled source code if the compilation was successful.
        const char* sourceCode;

        //! The output file path if applicable.
        const char* outputFilePath;

        //! The error message if the compilation failed.
        const char* errorMessage;
    };

	//! Free a c_CompileResult and frees associated memory.
	//! @param result The c_CompileResult to destroy.
    void free_compile_result(c_CompileResult* result);
}
//! Converts a C++ CompileResult to a C-style c_CompileResult.
//! @param result The C++ CompileResult to convert.
//! @return A pointer to the newly created c_CompileResult.
c_CompileResult* c_to_cpp_CompileResult(const ris_shader_toolkit::CompileResult& result);

//! Creates a c_CompileResult representing an error with the given message.
//! @param errorMessage The error message.
//! @return A c_CompileResult representing the error.
c_CompileResult* errorResult(const char* errorMessage);

#endif //COMPILER_RESULT_C_H
