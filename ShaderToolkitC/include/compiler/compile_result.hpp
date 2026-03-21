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
        //! @param sourceCode The compiled source code if the compilation was successful.
        //! @param error The error message if the compilation failed.
        CompileResult(bool success, const std::string& sourceCode, const std::string& error = "");

        //! Constructs a CompileResult object with reflection data.
        //! @param sourceCode The compiled source code if the compilation was successful.
        //! @param reflectionData The reflection data from the compilation.
        CompileResult(const std::string& sourceCode, ShaderReflection reflectionData);

        //! Constructs a CompileResult object.
        //! @param success True if the compilation was successful, false otherwise.
        //! @param sourceCode The compiled source code in binary format if the compilation was successful.
        //! @param error The error message if the compilation failed.
        CompileResult(bool success, const std::vector<uint32_t>& sourceCode, const std::string& error = "");

        //! Constructs a CompileResult object with reflection data.
        //! @param sourceCode The compiled source code in binary format if the compilation was successful.
        //! @param reflectionData The reflection data from the compilation.
        CompileResult(const std::vector<uint32_t>& sourceCode, ShaderReflection reflectionData);

        //! Returns true if the compilation was successful, false otherwise.
        //! @return True if the compilation was successful, false otherwise.
        bool isSuccess() const { return _success; }

        //! Returns the reflection data from the compilation.
        //! @return The reflection data.
        ShaderReflection* getReflectionData() { return &_reflectionData; }

        //! Returns the compiled source code in binary format if the compilation was successful.
        //! @return The compiled source code in binary format if the compilation was successful or an empty string otherwise.
        const std::vector<uint32_t>& getBinaryCode() const { return _binarySourceCode; }

        //! Returns the compiled source code if the compilation was successful.
		//! @return The compiled source code if the compilation was successful or an empty string otherwise.
        std::string getSourceCode() const { return _sourceCode; }

        //! Returns the error message if the compilation failed.
        //! @return The error message if the compilation failed.
        std::string getErrorMessage() const { return _errorMessage; }

        //! Creates a successful CompileResult object.
        //! @param sourceCode The compiled source code.
        //! @param reflectionData The reflection data from the compilation.
        //! @return A successful CompileResult object.
        static CompileResult successResult(const std::string& sourceCode, ShaderReflection reflectionData);

        //! Creates a successful CompileResult object.
        //! @param binaryCode The compiled source code in binary format.
        //! @param reflectionData The reflection data from the compilation.
        //! @return A successful CompileResult object.
        static CompileResult successResult(const std::vector<uint32_t>& binaryCode, ShaderReflection reflectionData);

        //! Creates a failed CompileResult object.
        //! @param errorMessage The error message.
        //! @return A failed CompileResult object.
        static CompileResult errorResult(const std::string& errorMessage);

    private:
        bool _success;
        std::string _sourceCode;
        std::vector<uint32_t> _binarySourceCode;
        std::string _errorMessage;
        ShaderReflection _reflectionData;
    };
}

#endif //COMPILE_RESULT_H
