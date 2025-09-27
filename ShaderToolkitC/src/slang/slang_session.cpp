//
// Created by lukaa on 27.9.2025..
//

#include "slang/slang_session.hpp"

namespace shader_toolkit {

   bool SlangSession::initialize() {
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

}