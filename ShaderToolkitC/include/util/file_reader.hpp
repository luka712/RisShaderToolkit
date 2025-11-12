#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>

namespace ris_shader_toolkit {
    class FileReader {
      public:
        //! Reads the contents of a file and returns it as a string.
        //! @param filePath The path to the file to read.
        //! @return The contents of the file as a string.
       std::string read(const std::string& filePath);
    };
}

#endif //FILE_READER_H
