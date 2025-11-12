#include "util/file_reader.hpp"
#include <fstream>
#include <sstream>


namespace ris_shader_toolkit {

	std::string FileReader::read(const std::string& filePath)
	{
		std::ifstream file(filePath);
		if (!file.is_open())
			throw std::runtime_error("Failed to open file: " + filePath);

		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}
}