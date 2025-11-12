#ifndef GLSLANG_COMPILER_RESULT_H
#define GLSLANG_COMPILER_RESULT_H

#include <string>

namespace ris_shader_toolkit {

    //! A class that represents the result of a glslang compilation.
    class GlslangCompileResult
    {
    public:
        //! Constructs a GlslangCompileResult object.
        //! @param success True if the compilation was successful, false otherwise.
        //! @param sourceCode The compiled source code if the compilation was successful.
        //! @param error The error message if the compilation failed.
        GlslangCompileResult(bool success, const std::string& sourceCode, const std::string& error = "");

        //! Returns true if the compilation was successful, false otherwise.
        //! @return True if the compilation was successful, false otherwise.
        bool isSuccess() const { return success; }

        //! Returns the compiled source code if the compilation was successful.
        //! @return The compiled source code if the compilation was successful.
        std::string getSourceCode() const { return sourceCode; }

        //! Returns the error message if the compilation failed.
        //! @return The error message if the compilation failed.
        std::string getErrorMessage() const { return errorMessage; }

        //! Creates a successful SlangCompileResult object.
        //! @param sourceCode The compiled source code.
        //! @return A successful SlangCompileResult object.
        static GlslangCompileResult successResult(const std::string& sourceCode);

        //! Creates a failed SlangCompileResult object.
        //! @param errorMessage The error message.
        //! @return A failed SlangCompileResult object.
        static GlslangCompileResult errorResult(const std::string& errorMessage);

    private:
        bool success = false;
        std::string sourceCode;
        std::string errorMessage;
    };
}

#endif //GLSLANG_COMPILER_RESULT_H
