#ifndef SLANG_SESSION_H
#define SLANG_SESSION_H

#include <slang.h>
#include <slang-com-ptr.h>
#include <string>
#include <map>
#include "slang/slang_compile_result.hpp"
#include "data/enums.hpp"

using Slang::ComPtr;

namespace shader_toolkit {

	//! A class that manages the Slang global session.
	class SlangSession
	{
	public:

		//! Constructs a SlangSession object.
		SlangSession();

		//! Initializes the Slang global session.
		bool initialize();

		//! Gets the Slang global session.
		//! @return The Slang global session.
		ComPtr<slang::IGlobalSession> getSession() const { return session; }

		//! Compiles a Slang shader file to the specified target and profile. 
		//! This is low-level function that directly uses the Slang API.
		//! @param filePath The path to the Slang shader file.
		//! @param compileTarget The target to compile to (e.g., SLANG_HLSL).
		//! @param profile The profile to compile to (e.g., "sm_5_0").
		//! @param stage The shader stage (e.g., SLANG_STAGE_VERTEX). Default is SLANG_STAGE_VERTEX.
		//! @param entryPoint The entry point function name (default is "main").
		SlangCompileResult compile(
			const std::string& filePath,
			SlangCompileTarget compileTarget,
			const std::string& profile,
			SlangStage stage = SLANG_STAGE_VERTEX,
			const std::string& entryPoint = "main"
		);

		//! Compiles an HLSL shader file to the specified profile and stage.
		//! @param filePath The path to the HLSL shader file.
		//! @param stage The shader stage (e.g., ShaderStage::Vertex). By default, it is ShaderStage::Vertex.
		//! @param entryPoint The entry point function name (default is "main").
		//! @param profile The HLSL profile to compile to (e.g., "sm_5_0"). By default, it is HlslProfile::SM_5_0.
		SlangCompileResult compileToHlsl(
			const std::string& filePath,
			ShaderStage stage = ShaderStage::Vertex,
			const std::string& entryPoint = "main",
			HlslProfile profile = HlslProfile::SM_5_0);

	private:
		ComPtr<slang::IGlobalSession> session;

		std::map<ShaderStage, SlangStage> shaderStageMap;
		std::map<HlslProfile, std::string> hlslProfileMap;
	};
};


#endif // SLANG_SESSION_H