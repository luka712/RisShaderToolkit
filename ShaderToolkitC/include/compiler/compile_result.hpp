#ifndef COMPILE_RESULT_H
#define COMPILE_RESULT_H

#include <string>

namespace shader_toolkit {
    //! A class that represents the result of compilation.
    class CompileResult
    {
    public:
        //! Constructs a CompileResult object.
        //! @param success True if the compilation was successful, false otherwise.
        //! @param outputFilePath The output file path.
        //! @param sourceCode The compiled source code if the compilation was successful.
        //! @param error The error message if the compilation failed.
        CompileResult(bool success, const std::string& outputFilePath, const std::string& sourceCode, const std::string& error = "");

        //! Returns true if the compilation was successful, false otherwise.
        //! @return True if the compilation was successful, false otherwise.
        bool isSuccess() const { return success; }

        //! Returns the output file path.
		//! @return The output file path if the compilation was successful or an empty string otherwise.
        std::string getOutputFilePath() const { return outputFilePath; }

        //! Returns the compiled source code if the compilation was successful.
		//! @return The compiled source code if the compilation was successful or an empty string otherwise.
        std::string getSourceCode() const { return sourceCode; }

        //! Returns the error message if the compilation failed.
        //! @return The error message if the compilation failed.
        std::string getErrorMessage() const { return errorMessage; }

        //! Creates a successful CompileResult object.
        //! @param outputFilePath The output file path.
        //! @param sourceCode The compiled source code.
        //! @return A successful CompileResult object.
        static CompileResult successResult(const std::string& outputFilePath, const std::string& sourceCode);

        //! Creates a failed CompileResult object.
        //! @param errorMessage The error message.
        //! @return A failed CompileResult object.
        static CompileResult errorResult(const std::string& errorMessage);

    private:
        bool success = false;
        std::string sourceCode;
        std::string outputFilePath;
        std::string errorMessage;
    };
}

#endif //COMPILE_RESULT_H
