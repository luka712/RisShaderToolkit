#include "compiler/c_rules.hpp"

ris_shader_toolkit::ReplaceStageInputNameRule* c_to_cpp_ReplaceStageInputNameRule(const c_ReplaceStageInputNameRule* c_rule)
{
	if (c_rule == nullptr) {
		return nullptr;
	}

	ris_shader_toolkit::ReplaceStageInputNameRule* cpp_rule = new ris_shader_toolkit::ReplaceStageInputNameRule();

	if (c_rule->prefix != nullptr) {
		cpp_rule->setPrefix(std::string(c_rule->prefix));
	}

	return cpp_rule;
}

ris_shader_toolkit::ReplaceStageOutputNameRule* c_to_cpp_ReplaceStageOutputNameRule(const c_ReplaceStageOutputNameRule* c_rule)
{
	if (c_rule == nullptr) {
		return nullptr;
	}

	ris_shader_toolkit::ReplaceStageOutputNameRule* cpp_rule = new ris_shader_toolkit::ReplaceStageOutputNameRule();
	if (c_rule->prefix != nullptr) {
		cpp_rule->setPrefix(std::string(c_rule->prefix));
	}
	cpp_rule->setTrimEntryPointName(c_rule->trimEntryPointName);
	return cpp_rule;
}
