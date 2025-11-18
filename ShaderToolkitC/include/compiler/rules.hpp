#ifndef RULE_H
#define RULE_H

#include <string>

namespace ris_shader_toolkit
{
	//! A rule that replaces the input variable names of a shader stage.
	//! For example, we can add a prefix to all input variable names of a vertex shader or any other stage.
	//! Example usage:
	//! ReplaceStageInputNameRule rule;
	//! rule.setPrefix("v_");
	//! This will rename an input variable named "in vec3 position" to "in vec3 v_position".
	class ReplaceStageInputNameRule {

	public:

		//! Gets the prefix to be added to input variable names.
		//! @return The prefix string.
		inline std::string getPrefix() const {
			return prefix;
		}

		//! Sets the prefix to be added to input variable names.
		//! @param prefix The prefix string to be removed.
		inline void setPrefix(const std::string& prefix) {
			this->prefix = prefix;
		}

	private:
		std::string prefix = "";
	};

	//! A rule that replaces the output variable names of a shader stage.
	//! For example, we can add a prefix to all output variable names of a vertex shader or any other stage.
	//! Example usage:
	//! ReplaceStageOutputNameRule rule;
	//! rule.setPrefix("o_");
	//! This will rename an output variable named "out vec3 color" to "out vec3 o_color".
	class ReplaceStageOutputNameRule {
	public:

		//! Gets the prefix to be added to output variable names.
		//! @return The prefix string.
		inline std::string getPrefix() const {
			return prefix;
		}

		//! Sets the prefix to be added to output variable names.
		//! @param prefix The prefix string to be removed.
		inline void setPrefix(const std::string& prefix) {
			this->prefix = prefix;
		}

		//! Gets whether to trim the entry point name from output variable names.
		//! @return True if trimming is enabled, false otherwise.
		inline bool getTrimEntryPointName() const {
			return trimEntryPointName;
		}

		//! Sets whether to trim the entry point name from output variable names.
		//! Entry point names are typically prefixed to output variable names in some shading languages.
		//! For example, an output variable named "entryPointParam_main_fs.color" or "main_fs.color" would be trimmed to "color" if this option is enabled.
		//! NOTE: Not all results will have entry point name.
		//! @param trim Whether to trim the entry point name.
		inline void setTrimEntryPointName(bool trim) {
			this->trimEntryPointName = trim;
		}

	private:
		std::string prefix = "";
		bool trimEntryPointName = false;
	};
}

#endif //RULE_H
