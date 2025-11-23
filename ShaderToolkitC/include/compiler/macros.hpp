#pragma once

#ifndef API_EXPORT

#define API_EXPORT

#if defined(_WIN32) || defined(_WIN64)
    #define API_EXPORT __declspec(dllexport)
#else
    // For Linux / macOS using GCC or Clang
    #define API_EXPORT __attribute__((visibility("default")))
#endif

#endif // API_EXPORT