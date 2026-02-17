
#ifndef SHADER_BINDING_H
#define SHADER_BINDING_H

#include <string>
#include "data/enums.hpp"
#include <vector>
#include <cstdint>

namespace ris_shader_toolkit {

	struct ShaderBinding;

	//! A class that represents reflection data from compilation.
	struct ShaderReflection
	{
		//! The bindings of the shader.
		std::vector<ShaderBinding> bindings;
	};

	//! A structure that represents a shader binding.
	struct ShaderBinding
	{
		//! The name of the shader binding.
		std::string name;

		//! The set number of the shader binding.
		uint32_t set;

		//! The binding number of the shader binding.
		uint32_t binding;

		//! The type of the shader resource.
		BindingType type;

		//! The size of the shader binding in bytes.
		size_t size;
	};
}
#endif //SHADER_BINDING_H
