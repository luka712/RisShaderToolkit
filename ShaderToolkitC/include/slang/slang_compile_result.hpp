//
// Created by Erkapic Luka on 1.10.2025.
//

#ifndef SLANG_COMPILE_RESULT_H
#define SLANG_COMPILE_RESULT_H

#include <string>
#include "data/shader_reflection.hpp"

namespace ris_shader_toolkit {

	//! A class that represents the result of a Slang compilation.
	class SlangCompileResult
	{
	public:
		//! Constructs a SlangCompileResult object.
		//! @param success True if the compilation was successful, false otherwise.
		//! @param sourceCode The compiled source code if the compilation was successful.
		//! @param shaderReflection The shader reflection data if the compilation was successful.
		//! @param error The error message if the compilation failed.
		SlangCompileResult(bool success, const std::string& sourceCode, ShaderReflection shaderReflection, const std::string& error = "");

		//! Constructs a SlangCompileResult object.
		//! @param success True if the compilation was successful, false otherwise.
		//! @param binaryCode The compiled source code as binary if the compilation was successful. Binary code is used for targets like SPIR-V.
		//! @param shaderReflection The shader reflection data if the compilation was successful.
		//! @param error The error message if the compilation failed.
		SlangCompileResult(bool success, const std::vector<uint8_t>& binaryCode, ShaderReflection shaderReflection, const std::string& error = "");

		//! Returns true if the compilation was successful, false otherwise.
		//! @return True if the compilation was successful, false otherwise.
		bool isSuccess() const { return _success; }

		//! Returns the compiled source code if the compilation was successful.
		//! @return The compiled source code if the compilation was successful.
		std::string getSourceCode() const { return _sourceCode; }

		//! Returns the compiled binary source code if the compilation was successful.
		//! @return The compiled binary source code if the compilation was successful.
		const std::vector<uint8_t>& getBinaryCode() const { return _binaryCode; }

		//! Returns the error message if the compilation failed.
		//! @return The error message if the compilation failed.
		std::string getErrorMessage() const { return _errorMessage; }

		//! Creates a successful SlangCompileResult object.
		//! @param sourceCode The compiled source code.
		//! @param reflectionData The reflection data from the compilation.
		//! @return A successful SlangCompileResult object.
		static SlangCompileResult successResult(const std::string& sourceCode, ShaderReflection reflectionData);

		//! Creates a successful SlangCompileResult object.
		//! @param binaryCode The compiled source code in binary format.
		//! @param reflectionData The reflection data from the compilation.
		//! @return A successful SlangCompileResult object.
		static SlangCompileResult successResult(const std::vector<uint8_t>& binaryCode, ShaderReflection reflectionData);

		//! Creates a failed SlangCompileResult object.
		//! @param errorMessage The error message.
		//! @return A failed SlangCompileResult object.
		static SlangCompileResult errorResult(const std::string& errorMessage);

	private:
		bool _success = false;
		std::string _sourceCode;
        std::vector<uint8_t> _binaryCode;
		std::string _errorMessage;
		ShaderReflection _reflectionData;
	};
}
#endif //SLANG_COMPILE_RESULT_H
