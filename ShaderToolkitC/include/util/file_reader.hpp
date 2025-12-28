#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <vector>
#include <cstdint>

namespace ris_shader_toolkit {
    class FileReader {
      public:
        //! Reads the contents of a file and returns it as a string.
        //! @param filePath The path to the file to read.
        //! @return The contents of the file as a string.
       std::string read(const std::string& filePath);

	   //! Reads a binary file and returns its contents as a vector of uint32_t.
	   //! @param path The path to the binary file to read.
	   //! @return The contents of the file as a vector of uint32_t.
       std::vector<uint32_t> readAsU32(const std::string& path);
    };
}

#endif //FILE_READER_H
