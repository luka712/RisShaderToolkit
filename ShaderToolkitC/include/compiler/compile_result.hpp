#ifndef COMPILE_RESULT_H
#define COMPILE_RESULT_H

#include <string>
#include <vector>
#include "data/shader_reflection.hpp"

namespace ris_shader_toolkit {

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

        //! Constructs a CompileResult object with reflection data.
        //! @param outputFilePath The output file path.
        //! @param sourceCode The compiled source code if the compilation was successful.
        //! @param reflectionData The reflection data from the compilation.
        CompileResult(const std::string& outputFilePath, const std::string& sourceCode, ShaderReflection reflectionData);

        //! Returns true if the compilation was successful, false otherwise.
        //! @return True if the compilation was successful, false otherwise.
        bool isSuccess() const { return _success; }

        //! Returns the reflection data from the compilation.
        //! @return The reflection data.
        ShaderReflection* getReflectionData() { return &_reflectionData; }

        //! Returns the output file path.
		//! @return The output file path if the compilation was successful or an empty string otherwise.
        std::string getOutputFilePath() const { return _outputFilePath; }

        //! Returns the compiled source code if the compilation was successful.
		//! @return The compiled source code if the compilation was successful or an empty string otherwise.
        std::string getSourceCode() const { return _sourceCode; }

        //! Returns the error message if the compilation failed.
        //! @return The error message if the compilation failed.
        std::string getErrorMessage() const { return _errorMessage; }

        //! Creates a successful CompileResult object.
        //! @param outputFilePath The output file path.
        //! @param sourceCode The compiled source code.
        //! @param reflectionData The reflection data from the compilation.
        //! @return A successful CompileResult object.
        static CompileResult successResult(const std::string& outputFilePath, const std::string& sourceCode, ShaderReflection reflectionData);

        //! Creates a failed CompileResult object.
        //! @param errorMessage The error message.
        //! @return A failed CompileResult object.
        static CompileResult errorResult(const std::string& errorMessage);

    private:
        bool _success;
        std::string _sourceCode;
        std::string _outputFilePath;
        std::string _errorMessage;
        ShaderReflection _reflectionData;
    };
}

#endif //COMPILE_RESULT_H
