#ifndef SPIRV_CROSS_COMPILE_RESULT_HPP
#define SPIRV_CROSS_COMPILE_RESULT_HPP

#include <string>

namespace ris_shader_toolkit {

    //! A class that represents the result of a Spir-V Cross compilation.
    class SpirVCrossCompileResult
    {
    public:
        //! Constructs a SpirVCrossCompileResult object.
        //! @param success True if the compilation was successful, false otherwise.
        //! @param sourceCode The compiled source code if the compilation was successful.
        //! @param error The error message if the compilation failed.
        SpirVCrossCompileResult(bool success, const std::string& sourceCode, const std::string& error = "");

        //! Returns true if the compilation was successful, false otherwise.
        //! @return True if the compilation was successful, false otherwise.
        bool isSuccess() const { return success; }

        //! Returns the compiled source code if the compilation was successful.
        //! @return The compiled source code if the compilation was successful.
        std::string getSourceCode() const { return sourceCode; }

        //! Returns the error message if the compilation failed.
        //! @return The error message if the compilation failed.
        std::string getErrorMessage() const { return errorMessage; }

        //! Creates a successful SpirVCrossCompileResult object.
        //! @param sourceCode The compiled source code.
        //! @return A successful SpirVCrossCompileResult object.
        static SpirVCrossCompileResult successResult(const std::string& sourceCode);

        //! Creates a failed SpirVCrossCompileResult object.
        //! @param errorMessage The error message.
        //! @return A failed SpirVCrossCompileResult object.
        static SpirVCrossCompileResult errorResult(const std::string& errorMessage);

    private:
        bool success = false;
        std::string sourceCode;
        std::string errorMessage;
    };
}

#endif //SPIRV_CROSS_COMPILE_RESULT_HPP
