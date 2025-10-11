
#ifndef FXC_COMPILE_RESULT_H
#define FXC_COMPILE_RESULT_H

#include <string>

namespace shader_toolkit
{
    class FxcCompileResult
    {
    public:
        //! Constructs a FxcCompileResult object.
        //! @param success True if the compilation was successful, false otherwise.
        //! @param sourceCode The compiled source code if the compilation was successful.
        //! @param error The error message if the compilation failed.
        FxcCompileResult(bool success, const std::string& sourceCode, const std::string& error = "");

        //! Returns true if the compilation was successful, false otherwise.
        //! @return True if the compilation was successful, false otherwise.
        bool isSuccess() const { return success; }

        //! Returns the compiled source code if the compilation was successful.
        //! @return The compiled source code if the compilation was successful.
        std::string getSourceCode() const { return sourceCode; }

        //! Returns the error message if the compilation failed.
        //! @return The error message if the compilation failed.
        std::string getErrorMessage() const { return errorMessage; }

        //! Creates a successful FxcCompileResult object.
        //! @param sourceCode The compiled source code.
        //! @return A successful FxcCompileResult object.
        static FxcCompileResult successResult(const std::string& sourceCode);

        //! Creates a failed FxcCompileResult object.
        //! @param errorMessage The error message.
        //! @return A failed FxcCompileResult object.
        static FxcCompileResult errorResult(const std::string& errorMessage);

    private:
        bool success = false;
        std::string sourceCode;
        std::string errorMessage;
    };
      };

#endif //FXC_COMPILE_RESULT_H
