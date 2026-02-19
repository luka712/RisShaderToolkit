#include "slang/c_slang.hpp"
#include <slang.h>
#include <slang-com-ptr.h>

SlangResult slangCreateGlobalSession(slang::IGlobalSession* globalSessionPtr)
{
    slang::IGlobalSession *globalSession;
    SlangResult res = slang::createGlobalSession(&globalSession);
    globalSessionPtr = globalSession;
    return res;
}

void slangReleaseGlobalSession(slang::IGlobalSession* globalSessionPtr)
{
    if (globalSessionPtr != nullptr)
    {
        globalSessionPtr->Release();
    }
}