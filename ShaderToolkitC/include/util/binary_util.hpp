#ifndef BINARY_UTIL_H
#define BINARY_UTIL_H

#include <vector>
#include <string>
#include <cstdint>

namespace ris_shader_toolkit {

    //! Converts a string to a vector of given type T.
    //! @param str The input string.
    //! @return A vector of T representing the string data.
    template<typename T>
    std::vector<T> stringToBinary(const std::string& str) {
        std::vector<T> spirvBinary;
        size_t size = str.size();
        spirvBinary.resize(size / sizeof(T));
        std::memcpy(spirvBinary.data(), str.data(), size);
        return spirvBinary;
      }

}

#endif //BINARY_UTIL_H
