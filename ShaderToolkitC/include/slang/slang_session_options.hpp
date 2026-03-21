
#ifndef SLANG_SESSION_OPTIONS_HPP
#define SLANG_SESSION_OPTIONS_HPP

#include <slang.h>

namespace ris_shader_toolkit
{
    struct SlangSessionOptions {


        SlangSessionOptions() : matrixLayoutMode(SLANG_MATRIX_LAYOUT_MODE_UNKNOWN) {}

		//! The matrix layout mode to use for the Slang session.
        //! This option determines how matrices are laid out in memory and how they are accessed in shaders.
        //! The default value is SLANG_MATRIX_LAYOUT_MODE_UNKNOWN, which means that the matrix layout mode 
        //! will be determined by the Slang compiler based on the target and profile.
        //! You can set this option to SLANG_MATRIX_LAYOUT_ROW_MAJOR or SLANG_MATRIX_LAYOUT_COLUMN_MAJOR to 
        //! explicitly specify the matrix layout mode for the session.
        SlangMatrixLayoutMode matrixLayoutMode;
    };
}

#endif //SLANG_SESSION_OPTIONS_HPP
