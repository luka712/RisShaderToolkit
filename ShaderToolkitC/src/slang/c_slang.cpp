#include "slang/c_slang.hpp"
#include <slang.h>
#include <slang-com-ptr.h>

const char* slang_get_last_error_message()
{
	return slangLastErrorMessage.c_str();
}

SlangResult slang_create_global_session(slang::IGlobalSession** globalSessionPtr)
{
	return slang::createGlobalSession(globalSessionPtr);
}

void slang_release_global_session(slang::IGlobalSession* globalSessionPtr)
{
	if (globalSessionPtr == nullptr)
	{
		slangLastErrorMessage = "Global session pointer is null.";
		return;
	}

	globalSessionPtr->Release();
}

SlangResult slang_create_session(
	slang::IGlobalSession* globalSessionPtr,
	slang::SessionDesc sessionDesc,
	slang::ISession** sessionPtr)
{
	if (globalSessionPtr != nullptr && sessionPtr != nullptr)
	{
		slang::IGlobalSession* globalSession = static_cast<slang::IGlobalSession*>(globalSessionPtr);
		return globalSession->createSession(sessionDesc, sessionPtr);
	}
	slangLastErrorMessage = "Global session pointer or session pointer is null.";
	return SLANG_E_INVALID_ARG;
}

SlangProfileID slang_find_profile(slang::IGlobalSession* globalSessionPtr, const char* name)
{
	if (globalSessionPtr != nullptr)
	{
		slang::IGlobalSession* globalSession = static_cast<slang::IGlobalSession*>(globalSessionPtr);
		return globalSession->findProfile(name);
	}
	slangLastErrorMessage = "Global session pointer is null.";
	return SLANG_PROFILE_UNKNOWN;
}