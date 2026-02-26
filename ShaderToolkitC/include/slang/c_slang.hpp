#include "macros.hpp"
#include <slang.h>

extern "C" {

	//! Creates a new Compiler instance.
	//! @param globalSessionPtr A pointer to a pointer that will receive the created Slang global session instance.
	//! @return True if the global session was created successfully, false otherwise.
	API_EXPORT
	SlangResult slang_create_global_session(slang::IGlobalSession** globalSessionPtr);

	//! Releases the Slang global session instance.
	// @param globalSessionPtr A pointer to the Slang global session instance to be released.
	API_EXPORT
	void slang_release_global_session(slang::IGlobalSession* globalSessionPtr);

	API_EXPORT
	SlangProfileID slang_find_profile(slang::IGlobalSession* globalSessionPtr, const char* profileName);
}