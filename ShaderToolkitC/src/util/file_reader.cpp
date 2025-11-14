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

	// Load SPIR-V file into uint32_t buffer
	std::vector<uint32_t> FileReader::readAsU32(const std::string& path)
	{
		std::ifstream file(path, std::ios::binary | std::ios::ate);
		if (!file)
			throw std::runtime_error("Failed to open file: " + path);

		size_t size = (size_t)file.tellg();
		file.seekg(0);

		std::vector<uint32_t> data(size / sizeof(uint32_t));
		file.read((char*)data.data(), size);
		return data;
	}
}