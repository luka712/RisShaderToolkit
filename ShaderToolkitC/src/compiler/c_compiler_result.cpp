#include "compiler/c_compiler_result.hpp"

void free_compile_result(c_CompileResult* result)
{
	if (result != nullptr) {
		// Free the allocated strings if they are not null
		if (result->sourceCode != nullptr) {
			delete[] result->sourceCode;
		}
		if (result->binaryCode != nullptr) {
			delete[] result->binaryCode;
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
	cResult->sourceCode = result.getSourceCode().empty() ? nullptr : strdup(result.getSourceCode().c_str());
	cResult->errorMessage = result.getErrorMessage().empty() ? nullptr : strdup(result.getErrorMessage().c_str());

	size_t binarySize = result.getBinaryCode().size();
	if(binarySize > 0)
	{
		auto destBinary = new uint8_t[binarySize];
		for (size_t i = 0; i < binarySize; i++)
		{
			auto& srcBinary = result.getBinaryCode();
			destBinary[i] = srcBinary[i];
		}
		cResult->binaryCode = destBinary;
	}
	else
	{
		cResult->binaryCode = nullptr;
	}
	cResult->binaryCodeSize = binarySize;
	cResult->sourceCodeSize = result.getSourceCode().size();
	cResult->errorMessageSize = result.getErrorMessage().size();
	return cResult;
}

c_CompileResult* errorResult(const char* errorMessage)
{
	c_CompileResult* result = new c_CompileResult();
	result->success = false;
	result->sourceCode = nullptr;
	result->binaryCode = nullptr;
	result->errorMessage = strdup(errorMessage);
	result->sourceCodeSize = 0;
	result->binaryCodeSize = 0;
	result->errorMessageSize = strlen(errorMessage);
	return result;
}
