#include "compiler/c_compiler_result.hpp"

void free_compile_result(c_CompileResult* result)
{
	if (result != nullptr) {
		// Free the allocated strings if they are not null
		if (result->sourceCode != nullptr) {
			delete[] result->sourceCode;
		}
		if (result->outputFilePath != nullptr) {
			delete[] result->outputFilePath;
		}
		if (result->errorMessage != nullptr) {
			delete[] result->errorMessage;
		}
		// Finally, free the result structure itself
		delete result;
	}
}

c_CompileResult* c_to_cpp_CompileResult(const ris_shader_toolkit::CompileResult& result)
{
	c_CompileResult* cResult = new c_CompileResult();
	cResult->success = result.isSuccess();
	cResult->sourceCode = result.getSourceCode().empty() ? nullptr : _strdup(result.getSourceCode().c_str());
	cResult->outputFilePath = result.getOutputFilePath().empty() ? nullptr : _strdup(result.getOutputFilePath().c_str());
	cResult->errorMessage = result.getErrorMessage().empty() ? nullptr : _strdup(result.getErrorMessage().c_str());
	return cResult;
}

c_CompileResult* errorResult(const char* errorMessage)
{
	c_CompileResult* result = new c_CompileResult();
	result->success = false;
	result->sourceCode = nullptr;
	result->outputFilePath = nullptr;
	result->errorMessage = _strdup(errorMessage);
	return result;
}
