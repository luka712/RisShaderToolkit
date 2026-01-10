#ifndef SLANG_SESSION_H
#define SLANG_SESSION_H

#include <slang.h>
#include <slang-com-ptr.h>
#include <string>
#include <map>
#include "slang/slang_compile_result.hpp"
#include "data/enums.hpp"
#include <vector>

using Slang::ComPtr;

namespace ris_shader_toolkit {

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

		//! Compiles a Slang shader file to the specified target and profile. 
		//! This is low-level function that directly uses the Slang API.
		//! @param sourceStr The source code string.
		//! @param compileTarget The target to compile to (e.g., SLANG_HLSL).
		//! @param profile The profile to compile to (e.g., "sm_5_0").
		//! @param stage The shader stage (e.g., SLANG_STAGE_VERTEX). Default is SLANG_STAGE_VERTEX.
		//! @param entryPoint The entry point function name (default is "main").
		SlangCompileResult compileFromSourceCode(
			const std::string& sourceStr,
			SlangCompileTarget compileTarget,
			const std::string& profile,
			SlangStage stage = SLANG_STAGE_VERTEX,
			const std::string& entryPoint = "main"
		);

		//! Compiles a Slang shader file to the specified target and profile. 
		//! This is low-level function that directly uses the Slang API.
		//! @param filePath The path to the Slang shader file.
		//! @param compileTarget The target to compile to (e.g., SLANG_HLSL).
		//! @param profile The profile to compile to (e.g., "sm_5_0").
		//! @param stages The shader stages (e.g., SLANG_STAGE_VERTEX).
		//! @param entryPoints The entry points info function name. Must match the stages count.
		SlangCompileResult compile(
			const std::string& filePath,
			SlangCompileTarget compileTarget,
			const std::string& profile,
			std::vector<SlangStage> stages,
			std::vector<std::string> entryPoints
		);

		//! Compiles a Slang shader file to the specified target and profile. 
		//! This is low-level function that directly uses the Slang API.
		//! @param slangSourceCode The Slang shader source code.
		//! @param compileTarget The target to compile to (e.g., SLANG_HLSL).
		//! @param profile The profile to compile to (e.g., "sm_5_0").
		//! @param stages The shader stages (e.g., SLANG_STAGE_VERTEX).
		//! @param entryPoints The entry points info function name. Must match the stages count.
		SlangCompileResult compileFromSourceCode(
			const std::string& slangSourceCode,
			SlangCompileTarget compileTarget,
			const std::string& profile,
			std::vector<SlangStage> stages,
			std::vector<std::string> entryPoints
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

		//! Compiles an GLSL shader file to the specified profile and stage.
		//! @param filePath The path to the GLSL shader file.
		//! @param stage The shader stage (e.g., ShaderStage::Vertex). By default, it is ShaderStage::Vertex.
		//! @param entryPoint The entry point function name (default is "main").
		//! @param profile The GLSL profile to compile to (e.g., "450"). By default, it is GlslProfile::GL_450.
		SlangCompileResult compileToGlsl(
			const std::string& filePath,
			ShaderStage stage = ShaderStage::Vertex,
			const std::string& entryPoint = "main",
			GlslProfile profile = GlslProfile::GLSL_450);

		//! Compiles an GLSL shader file to the specified profile and stage.
		//! @param slangSourceCode The Slang shader source code.
		//! @param stage The shader stage (e.g., ShaderStage::Vertex). By default, it is ShaderStage::Vertex.
		//! @param entryPoint The entry point function name (default is "main").
		//! @param profile The GLSL profile to compile to (e.g., "450"). By default, it is GlslProfile::GL_450.
		SlangCompileResult compileSourceCodeToGlsl(
			const std::string& slangSourceCode,
			ShaderStage stage = ShaderStage::Vertex,
			const std::string& entryPoint = "main",
			GlslProfile profile = GlslProfile::GLSL_450);

		//! Compiles a Metal shader file to the specified profile and stage.
		//! @param filePath The path to the Metal shader file.
		//! @param stage The shader stage (e.g., ShaderStage::Vertex). By default, it is ShaderStage::Vertex.
		//! @param entryPoint The entry point function name (default is "main").
		//! @param profile The Metal profile to compile to (e.g., "metal2.0"). By default, it is MetalProfile::MSL_2_0.
		SlangCompileResult compileToMetal(
			const std::string& filePath,
			ShaderStage stage = ShaderStage::Vertex,
			const std::string& entryPoint = "main",
			MetalProfile profile = MetalProfile::MSL_2_0
		);

		//! Compiles a Metal shader file to the specified profile and stages.
		//! @param filePath The path to the Metal shader file.
		//! @param stages The shader stages (e.g., ShaderStage::Vertex).
		//! @param entryPoints The entry points info function name. Must match the stages count.
		//! @param profile The Metal profile to compile to (e.g., "metal2.0"). By default, it is MetalProfile::MSL_2_0.
		//! @return A SlangCompileResult object containing the result of the compilation.
		SlangCompileResult compileToMetal(
			const std::string& filePath,
			std::vector<ShaderStage> stages,
			std::vector<std::string> entryPoints,
			MetalProfile profile = MetalProfile::MSL_2_0
		);

		//! Compiles a ASlang shader to the SPIR-V shader file.
		//! @param filePath The path to the Slang shader file.
		//! @param stages The shader stages (e.g., ShaderStage::Vertex).
		//! @param entryPoints The entry points info function name. Must match the stages count.
		//! @param profile The SpirV profile to compile to (e.g., "spirv_1_5"). By default, it is SpirVProfile::SPIRV_1_5.
		//! @return A SlangCompileResult object containing the result of the compilation.
		SlangCompileResult compileToSpirV(
			const std::string& filePath,
			std::vector<ShaderStage> stages,
			std::vector<std::string> entryPoints,
			SpirVProfile profile = SpirVProfile::SPIRV_1_5
		);

		//! Compiles a ASlang shader to the SPIR-V shader file.
		//! @param sourceCode The Slang source code.
		//! @param stages The shader stages (e.g., ShaderStage::Vertex).
		//! @param entryPoints The entry points info function name. Must match the stages count.
		//! @param profile The SpirV profile to compile to (e.g., "spirv_1_5"). By default, it is SpirVProfile::SPIRV_1_5.
		//! @return A SlangCompileResult object containing the result of the compilation.
		SlangCompileResult compileSourceCodeToSpirV(
			const std::string& sourceCode,
			std::vector<ShaderStage> stages,
			std::vector<std::string> entryPoints,
			SpirVProfile profile = SpirVProfile::SPIRV_1_5
		);


	private:
		ComPtr<slang::IGlobalSession> session;

		std::map<ShaderStage, SlangStage> shaderStageMap;
		std::map<HlslProfile, std::string> hlslProfileMap;
		std::map<GlslProfile, std::string> glslProfileMap;
		std::map<MetalProfile, std::string> metalProfileMap;
		std::map<SpirVProfile, std::string> spirvProfileMap;
	};
};


#endif // SLANG_SESSION_H