#include "macros.hpp"
#include <slang.h>
#include <string>

extern "C" {

	//! Stores the last error message from the slang session.
	static std::string slangLastErrorMessage;

	//! Retrieves the last error message from slang session.
	//! @return The last error message as a string.
	const char* slang_get_last_error_message();

	//! Creates a new Compiler instance.
	//! @param globalSessionPtr A pointer to a pointer that will receive the created Slang global session instance.
	//! @return True if the global session was created successfully, false otherwise.
	API_EXPORT
	SlangResult slang_create_global_session(slang::IGlobalSession** globalSessionPtr);

	//! Releases the Slang global session instance.
	// @param globalSessionPtr A pointer to the Slang global session instance to be released.
	API_EXPORT
	void slang_release_global_session(slang::IGlobalSession* globalSessionPtr);

	//! Finds the profile ID for a given profile name.
	//! @param globalSessionPtr A pointer to the Slang global session instance.
	//! @param sessionDesc A description of the session to be created, including targets, flags, search paths, and other configuration options.
	//! @param sessionPtr A pointer to a pointer that will receive the created Slang session instance.
	//! @return True if the session was created successfully, false otherwise.
	API_EXPORT
	SlangResult slang_create_session(
		slang::IGlobalSession* globalSessionPtr,
		slang::SessionDesc sessionDesc,
		slang::ISession** sessionPtr);

	API_EXPORT
	SlangProfileID slang_find_profile(slang::IGlobalSession* globalSessionPtr, const char* profileName);
}