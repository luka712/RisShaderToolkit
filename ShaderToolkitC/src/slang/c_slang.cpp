#include "slang/c_slang.hpp"
#include <slang.h>
#include <slang-com-ptr.h>

SlangResult slang_create_global_session(slang::IGlobalSession** globalSessionPtr)
{
	return slang::createGlobalSession(globalSessionPtr);
}

void slang_release_global_session(slang::IGlobalSession* globalSessionPtr)
{
	if (globalSessionPtr != nullptr)
	{
		globalSessionPtr->Release();
	}
}

SlangProfileID slang_find_profile(slang::IGlobalSession* globalSessionPtr, const char* name)
{
	if (globalSessionPtr != nullptr)
	{
		slang::IGlobalSession* globalSession = static_cast<slang::IGlobalSession*>(globalSessionPtr);
		return globalSession->findProfile(name);
	}
	return SLANG_PROFILE_UNKNOWN;
}