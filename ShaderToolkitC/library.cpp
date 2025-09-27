#include "library.h"

#include <slang-com-ptr.h>
#include <slang.h>

using Slang::ComPtr;

bool create_session()
{
    // First we need to create slang global session with work with the Slang API.
    ComPtr<slang::IGlobalSession> slangGlobalSession;
    SlangResult res = slang::createGlobalSession(slangGlobalSession.writeRef());
    if (SLANG_FAILED(res))
    {
		// Print error.
		return false;
    }

    return true;
}