#ifndef SLANG_SESSION_H
#define SLANG_SESSION_H

#include <slang.h>
#include <slang-com-ptr.h>

using Slang::ComPtr;

namespace shader_toolkit {

    //! A class that manages the Slang global session.
    class SlangSession
    {
    public:

        //! Initializes the Slang global session.
        bool initialize();

        //! Gets the Slang global session.
        //! @return The Slang global session.
        ComPtr<slang::IGlobalSession> getSession() const { return session; }

        private:
            ComPtr<slang::IGlobalSession> session;
    };
};


#endif // SLANG_SESSION_H