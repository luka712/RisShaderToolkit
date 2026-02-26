#ifndef SLANG_SESSION_H
#define SLANG_SESSION_H

#include <slang.h>
#include <slang-com-ptr.h>
#include <string>
#include <map>
#include "slang/slang_compile_result.hpp"
#include "data/enums.hpp"
#include <vector>
#include <compiler/compile_result.hpp>

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
		ComPtr<slang::IGlobalSession> getGlobalSession() const { return _globalSession; }

		/// <summary>
		/// Returns the final compiled code from the Slang compile request. 
		/// It handles multiple entry points and concatenates the results if necessary.
		/// </summary>
		/// <param name="component">The component to read from.</param>
		/// <param name="entryPointCount">The entry points count.</param>
		/// <returns>The concatinated target code.</returns>
		std::string readCompiledCode(ComPtr<slang::IComponentType> component, size_t entryPointCount);

		/// <summary>
		/// Returns the final compiled code from the Slang compile request. 
		/// It handles multiple entry points and concatenates the results if necessary.
		/// </summary>
		/// <param name="component">The component to read from.</param>
		/// <param name="entryPointCount">The entry points count.</param>
		/// <returns>The concatinated target code.</returns>
		std::vector<uint8_t> readCompiledBinaryCode(ComPtr<slang::IComponentType> component, size_t entryPointCount);

		//! Compiles a Slang shader file to the specified target and profile. 
		//! This is low-level function that directly uses the Slang API.
		//! @param sourceCode The Slang shader source code.
		//! @param compileTarget The target to compile to (e.g., SLANG_HLSL).
		//! @param profile The profile to compile to (e.g., "sm_5_0"). Can be empty string when compiling to shader targets that do not require profile such as WGSL.
		//! @param stages The shader stages (e.g., SLANG_STAGE_VERTEX).
		//! @param entryPoints The entry points info function name. Must match the stages count.
		SlangCompileResult compile(
			const std::string& sourceCode,
			SlangCompileTarget compileTarget,
			std::string profile,
			std::vector<SlangStage> stages,
			std::vector<std::string> entryPoints
		);

		//! Compiles an HLSL shader file to the specified profile and stage.
		//! @param filePath The path to the HLSL shader file.
		//! @param stage The shader stage (e.g., ShaderStage::Vertex). By default, it is ShaderStage::Vertex.
		//! @param entryPoint The entry point function name (default is "main").
		//! @param profile The HLSL profile to compile to (e.g., "sm_5_0"). By default, it is HlslProfile::SM_5_0.
	/*	SlangCompileResult compileToHlsl(
			const std::string& filePath,
			ShaderStage stage = ShaderStage::Vertex,
			const std::string& entryPoint = "main",
			HlslProfile profile = HlslProfile::SM_5_0);*/

			//! Compiles an GLSL shader file to the specified profile and stage.
			//! @param filePath The path to the GLSL shader file.
			//! @param stage The shader stage (e.g., ShaderStage::Vertex). By default, it is ShaderStage::Vertex.
			//! @param entryPoint The entry point function name (default is "main").
			//! @param profile The GLSL profile to compile to (e.g., "450"). By default, it is GlslProfile::GL_450.
		/*	SlangCompileResult compileToGlsl(
				const std::string& filePath,
				ShaderStage stage = ShaderStage::Vertex,
				const std::string& entryPoint = "main",
				GlslProfile profile = GlslProfile::GLSL_450);*/

				//! Compiles an GLSL shader file to the specified profile and stage.
				//! @param slangSourceCode The Slang shader source code.
				//! @param stage The shader stage (e.g., ShaderStage::Vertex). By default, it is ShaderStage::Vertex.
				//! @param entryPoint The entry point function name (default is "main").
				//! @param profile The GLSL profile to compile to (e.g., "450"). By default, it is GlslProfile::GL_450.
				//SlangCompileResult compileSourceCodeToGlsl(
				//	const std::string& slangSourceCode,
				//	ShaderStage stage = ShaderStage::Vertex,
				//	const std::string& entryPoint = "main",
				//	GlslProfile profile = GlslProfile::GLSL_450);

				//! Compiles a Metal shader file to the specified profile and stage.
				//! @param filePath The path to the Metal shader file.
				//! @param stage The shader stage (e.g., ShaderStage::Vertex). By default, it is ShaderStage::Vertex.
				//! @param entryPoint The entry point function name (default is "main").
				//! @param profile The Metal profile to compile to (e.g., "metal2.0"). By default, it is MetalProfile::MSL_2_0.
				//SlangCompileResult compileToMetal(
				//	const std::string& filePath,
				//	ShaderStage stage = ShaderStage::Vertex,
				//	const std::string& entryPoint = "main",
				//	MetalProfile profile = MetalProfile::MSL_2_0
				//);

				//! Compiles a Metal shader file to the specified profile and stages.
				//! @param filePath The path to the Metal shader file.
				//! @param stages The shader stages (e.g., ShaderStage::Vertex).
				//! @param entryPoints The entry points info function name. Must match the stages count.
				//! @param profile The Metal profile to compile to (e.g., "metal2.0"). By default, it is MetalProfile::MSL_2_0.
				//! @return A SlangCompileResult object containing the result of the compilation.
				//SlangCompileResult compileToMetal(
				//	const std::string& filePath,
				//	std::vector<ShaderStage> stages,
				//	std::vector<std::string> entryPoints,
				//	MetalProfile profile = MetalProfile::MSL_2_0
				//);

				//! Compiles a WGSL shader file to the specified stages.
				//! @param slangSourceCode The Slang shader source code.
				//! @param stages The shader stages (e.g., ShaderStage::Vertex).
				//! @param entryPoints The entry points info function name. Can be empty if Slang source code is decorated with @entryPoint attributes.
				//! @return A SlangCompileResult object containing the result of the compilation.
		SlangCompileResult compileToWgsl(
			const std::string& slangSourceCode,
			std::vector<ShaderStage> stages,
			std::vector<std::string> entryPoints
		);

		//! Compiles a ASlang shader to the SPIR-V shader file.
		//! @param filePath The path to the Slang shader file.
		//! @param stages The shader stages (e.g., ShaderStage::Vertex).
		//! @param entryPoints The entry points info function name. Must match the stages count.
		//! @param profile The SpirV profile to compile to (e.g., "spirv_1_2"). By default, it is SpirVProfile::SPIRV_1_2.
		//! @return A SlangCompileResult object containing the result of the compilation.
		SlangCompileResult compileToSpirV(
			const std::string& filePath,
			std::vector<ShaderStage> stages,
			std::vector<std::string> entryPoints,
			SpirVProfile profile = SpirVProfile::SPIRV_1_2
		);


	private:
		ComPtr<slang::IGlobalSession> _globalSession;

		std::map<ShaderStage, SlangStage> shaderStageMap;
		std::map<HlslProfile, std::string> hlslProfileMap;
		std::map<GlslProfile, std::string> glslProfileMap;
		std::map<MetalProfile, std::string> metalProfileMap;
		std::map<SpirVProfile, std::string> spirvProfileMap;

		std::map< slang::TypeReflection::Kind, BindingType> _bindingTypeMap;

		//! Updates the shader code before compilation if needed.
		void modifyShader(slang::ICompileRequest* request, ShaderReflection* reflection);
	};
};


#endif // SLANG_SESSION_H