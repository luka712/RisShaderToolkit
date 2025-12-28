#ifndef C_RULES_H
#define C_RULES_H

#include "compiler/rules.hpp"
#include "compiler/macros.hpp"

extern "C" {
	API_EXPORT
	struct c_ReplaceStageInputNameRule {

		//! Gets the prefix to be added to input variable names.
		const char* prefix;
	};

	API_EXPORT
	struct c_ReplaceStageOutputNameRule {
		//! Gets the prefix to be added to output variable names.
		const char* prefix;

		//! Sets whether to trim the entry point name from output variable names.
		bool trimEntryPointName;
	};
}

//! Converts a C-style ReplaceStageInputNameRule to a C++ ReplaceStageInputNameRule.
//! @param c_rule The C-style ReplaceStageInputNameRule to convert.
//! @return A pointer to the newly created C++ ReplaceStageInputNameRule.
ris_shader_toolkit::ReplaceStageInputNameRule* c_to_cpp_ReplaceStageInputNameRule(const c_ReplaceStageInputNameRule* c_rule);

//! Converts a C-style ReplaceStageOutputNameRule to a C++ ReplaceStageOutputNameRule.
//! @param c_rule The C-style ReplaceStageOutputNameRule to convert.
//! @return A pointer to the newly created C++ ReplaceStageOutputNameRule.
ris_shader_toolkit::ReplaceStageOutputNameRule* c_to_cpp_ReplaceStageOutputNameRule(const c_ReplaceStageOutputNameRule* c_rule);

#endif //C_RULES_H
