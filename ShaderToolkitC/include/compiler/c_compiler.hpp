#include "compiler/compiler.hpp"
#include "compiler/c_compiler_result.hpp"
#include "compiler/c_rules.hpp"
#include "macros.hpp"

extern "C" {

	//! Stores the last error message from the compiler.
	//! NOTE: This is not thread-safe, as it uses a static variable.
	static std::string lastErrorMessage;

    //! Creates a new Compiler instance.
    //! @return A pointer to the created Compiler instance.
	API_EXPORT
	void* create_compiler();

	//! Retrieves the last error message from the compiler.
    API_EXPORT
	char* get_last_error_message();

 //   API_EXPORT
	//void* compile_slang_to_glsl(
	//	void* compilerPtr,
	//	const char* inputFilePath,
	//	int profile,           // GlslProfile as int
	//	int shaderStage,       // ShaderStage as int
	//	const char* entryPoint,
	//	c_ReplaceStageInputNameRule* inputRule,
	//	c_ReplaceStageOutputNameRule* outputRule
	//);

	//API_EXPORT
	//void* compile_slang_source_code_to_glsl(
	//void* compilerPtr,
	//const char* slangSourceCode,
	//int profile,           // GlslProfile as int
	//int shaderStage,       // ShaderStage as int
	//const char* entryPoint,
	//c_ReplaceStageInputNameRule* inputRule,
	//c_ReplaceStageOutputNameRule* outputRule
	//);

	API_EXPORT
	void* compile_slang_to_wgsl(
		void* compilerPtr,
		const char* slangSourceCode,
		int32_t* shaderStages,       
		uint32_t shaderStagesCount,
		const char** entryPoints,
		uint32_t entryPointsCount
	);

	API_EXPORT
    void* compile_slang_to_spirv(
		void* compilerPtr,
		const char* slangSourceCode,
		int32_t shaderStage,
		const char* entryPoint,
		ris_shader_toolkit::SpirVProfile profile
    );

	API_EXPORT
	void* compile_slang_to_glsl(
		void* compilerPtr,
		const char* slangSourceCode,
		int32_t shaderStage,
		const char* entryPoint,
		ris_shader_toolkit::GlslProfile profile
	);

    //! Frees the Compiler instance.
    //! @param compilerPtr A pointer to the Compiler instance to free.
    API_EXPORT
	void free_compiler(void* compilerPtr);
}
