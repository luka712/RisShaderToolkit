#ifndef XCRUN_COMPILE_RESULT_H
#define XCRUN_COMPILE_RESULT_H

#include <string>

namespace shader_toolkit
{
    //! The XcrunCompileResult class represents the result of a compilation using xcrun.
    class XcrunCompileResult
    {
    public:
        //! Constructs a XcrunCompileResult object.
        //! @param success True if the compilation was successful, false otherwise.
        //! @param sourceCode The compiled source code if the compilation was successful.
        //! @param error The error message if the compilation failed.
        XcrunCompileResult(bool success, const std::string& sourceCode, const std::string& error = "");

        //! Returns true if the compilation was successful, false otherwise.
        //! @return True if the compilation was successful, false otherwise.
        bool isSuccess() const { return success; }

        //! Returns the compiled source code if the compilation was successful.
        //! @return The compiled source code if the compilation was successful.
        std::string getSourceCode() const { return sourceCode; }

        //! Returns the error message if the compilation failed.
        //! @return The error message if the compilation failed.
        std::string getErrorMessage() const { return errorMessage; }

        //! Creates a successful XcrunCompileResult object.
        //! @param sourceCode The compiled source code.
        //! @return A successful XcrunCompileResult object.
        static XcrunCompileResult successResult(const std::string& sourceCode);

        //! Creates a failed XcrunCompileResult object.
        //! @param errorMessage The error message.
        //! @return A failed XcrunCompileResult object.
        static XcrunCompileResult errorResult(const std::string& errorMessage);

    private:
        bool success = false;
        std::string sourceCode;
        std::string errorMessage;
    };
}

#endif //XCRUN_COMPILE_RESULT_H
