//
// Created by Erkapic Luka on 1.10.2025.
//

#ifndef SLANG_COMPILE_RESULT_H
#define SLANG_COMPILE_RESULT_H

#include <string>

namespace ris_shader_toolkit {

	//! A class that represents the result of a Slang compilation.
	class SlangCompileResult
	{
	public:
		//! Constructs a SlangCompileResult object.
		//! @param success True if the compilation was successful, false otherwise.
		//! @param sourceCode The compiled source code if the compilation was successful.
		//! @param error The error message if the compilation failed.
		SlangCompileResult(bool success, const std::string& sourceCode, const std::string& error = "");

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
		static SlangCompileResult successResult(const std::string& sourceCode);

		//! Creates a failed SlangCompileResult object.
		//! @param errorMessage The error message.
		//! @return A failed SlangCompileResult object.
		static SlangCompileResult errorResult(const std::string& errorMessage);

	private:
		bool success = false;
		std::string sourceCode;
		std::string errorMessage;
	};
}
#endif //SLANG_COMPILE_RESULT_H
