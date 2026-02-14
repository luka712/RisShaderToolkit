#include "slang/slang_session.hpp"
#include <spdlog/spdlog.h>
#include <string>

namespace ris_shader_toolkit {
	SlangSession::SlangSession()
	{
		shaderStageMap = {
			{ ShaderStage::Vertex, SLANG_STAGE_VERTEX },
			{ ShaderStage::Fragment, SLANG_STAGE_FRAGMENT },
			{ ShaderStage::Compute, SLANG_STAGE_COMPUTE },
			//{ ShaderStage::Geometry, SLANG_STAGE_GEOMETRY },
			//{ ShaderStage::Hull, SLANG_STAGE_HULL },
			//{ ShaderStage::Domain, SLANG_STAGE_DOMAIN }
		};

		hlslProfileMap = {
			   { HlslProfile::SM_4_0, "sm_4_0" },
			   { HlslProfile::SM_4_1, "sm_4_1" },
			   { HlslProfile::SM_5_0, "sm_5_0" },
			   { HlslProfile::SM_5_1, "sm_5_1" },
			   { HlslProfile::SM_6_0, "sm_6_0" },
			   { HlslProfile::SM_6_1, "sm_6_1" },
			   { HlslProfile::SM_6_2, "sm_6_2" },
			   { HlslProfile::SM_6_3, "sm_6_3" },
			   { HlslProfile::SM_6_4, "sm_6_4" },
			   { HlslProfile::SM_6_5, "sm_6_5" },
		};

		glslProfileMap = {
			{ GlslProfile::GLSL_330, "glsl_330" },
			{ GlslProfile::GLSL_400, "glsl_400" },
			{ GlslProfile::GLSL_410, "glsl_410" },
			{ GlslProfile::GLSL_420, "glsl_420" },
			{ GlslProfile::GLSL_430, "glsl_430" },
			{ GlslProfile::GLSL_440, "glsl_440" },
			{ GlslProfile::GLSL_450, "glsl_450" },
			{ GlslProfile::GLSL_460, "glsl_460" },
		};

		metalProfileMap = {
			{ MetalProfile::MSL_1_0, "metallib_1_0" },
			{ MetalProfile::MSL_1_1, "metallib_1_1" },
			{ MetalProfile::MSL_1_2, "metallib_1_2" },
			{ MetalProfile::MSL_2_0, "metallib_2_0" },
			{ MetalProfile::MSL_2_1, "metallib_2_1" },
			{ MetalProfile::MSL_2_2, "metallib_2_2" },
			{ MetalProfile::MSL_2_3, "metallib_2_3" },
			{ MetalProfile::MSL_2_4, "metallib_2_4" }
		};

		spirvProfileMap = {
			{ SpirVProfile::SPIRV_1_0, "spirv_1_0" },
			{ SpirVProfile::SPIRV_1_1, "spirv_1_1" },
			{ SpirVProfile::SPIRV_1_2, "spirv_1_2" },
			{ SpirVProfile::SPIRV_1_3, "spirv_1_3" },
			{ SpirVProfile::SPIRV_1_4, "spirv_1_4" },
			{ SpirVProfile::SPIRV_1_5, "spirv_1_5" },
			{ SpirVProfile::SPIRV_1_6, "spirv_1_6" }
		};

		_bindingTypeMap = {
			{ slang::TypeReflection::Kind::ConstantBuffer, BindingType::UniformBuffer },
			{ slang::TypeReflection::Kind::Resource, BindingType::Resource},
			{ slang::TypeReflection::Kind::SamplerState, BindingType::SamplerState}
			// Add more mappings as needed
		};
	}

	bool SlangSession::initialize() {
		// First we need to create slang global session with work with the Slang API.
		SlangResult res = slang::createGlobalSession(_globalSession.writeRef());
		if (SLANG_FAILED(res))
		{
			// Print error.
			return false;
		}

		return true;
	}

	void SlangSession::modifyShader(slang::ICompileRequest* request, ShaderReflection* reflection)
	{
		slang::IComponentType* program = nullptr;
		request->getProgram(&program);

		slang::ProgramLayout* layout = program->getLayout(0);

		// Modify entry points.
		int entryPointCount = layout->getEntryPointCount();
		for (int i = 0; i < entryPointCount; i++)
		{
			slang::EntryPointLayout* entryPointLayout = layout->getEntryPointByIndex(i);
			const char* entryPointName = entryPointLayout->getName();
		}

		// Modify parameters
		int paramCount = layout->getParameterCount();
		for (int i = 0; i < paramCount; i++)
		{
			slang::VariableLayoutReflection* param = layout->getParameterByIndex(i);
			slang::TypeReflection* type = param->getType();
			slang::TypeReflection::Kind kind = type->getKind();
			SlangStage stage = param->getStage();
			slang::ParameterCategory category = param->getCategory();

			ShaderBinding binding;
			binding.name = param->getName();
			binding.set = param->getSemanticIndex();
			binding.binding = param->getBindingIndex();

			if (_bindingTypeMap.find(kind) == _bindingTypeMap.end())
			{
				spdlog::error("Unknown binding type for parameter: {}", binding.name);
				throw std::runtime_error("Unknown binding type encountered in SlangSession::modifyShader");
			}

			binding.type = _bindingTypeMap[kind];
			reflection->bindings.push_back(binding);
		}
	}

	SlangCompileResult SlangSession::compile(
		const std::string& filePath,
		SlangCompileTarget compileTarget,
		const std::string& profile,
		SlangStage stage,
		const std::string& entryPoint)
	{
		ComPtr<slang::ICompileRequest> request;
		_globalSession->createCompileRequest(request.writeRef());

		// Add your Slang source file.
		int translationUnitIndex = request->addTranslationUnit(SLANG_SOURCE_LANGUAGE_SLANG, entryPoint.c_str());
		request->addTranslationUnitSourceFile(translationUnitIndex, filePath.c_str());

		// Add target
		int targetIndex = request->addCodeGenTarget(compileTarget);

		// Set profile if it's defined.
		if (!profile.empty())
		{
			SlangProfileID profileID = _globalSession->findProfile(profile.c_str());
			if (profileID == SLANG_PROFILE_UNKNOWN)
			{
				return SlangCompileResult(false, "", ShaderReflection(), "Failed to find profile: " + profile);
			}
			request->setTargetProfile(targetIndex, profileID); // shader model
		}

		// Add entry point if not defined.
		if (!entryPoint.empty())
		{
			request->addEntryPoint(translationUnitIndex, entryPoint.c_str(), stage); // for VS
		}
		else
		{
			spdlog::debug("SlangSession:compile: Compiling without explicit entry point. Shader must have [shader(vertex|fragment...)} attribute ");
		}

		SlangResult res = request->compile();
		std::string diagnosticOutput = request->getDiagnosticOutput();
		if (SLANG_FAILED(res))
		{
			return SlangCompileResult(false, "", ShaderReflection(), diagnosticOutput);
		}
		else if (!diagnosticOutput.empty())
		{
			// Log info
			spdlog::info("Diagnostic output: ");
			spdlog::info(diagnosticOutput);
		}

		ShaderReflection reflection;
		modifyShader(request, &reflection);

		ComPtr<ISlangBlob> blob;
		request->getEntryPointCodeBlob(0, 0, blob.writeRef());

		std::string code = std::string((const char*)blob->getBufferPointer(), blob->getBufferSize());

		//std::cout << "Compilation succeeded!\n";
		return SlangCompileResult(true, code, reflection);
	}

	SlangCompileResult SlangSession::compileFromSourceCode(
		const std::string& sourceCodeStr,
		SlangCompileTarget compileTarget,
		const std::string& profile,
		SlangStage stage,
		const std::string& entryPoint)
	{
		ComPtr<slang::ICompileRequest> request;
		_globalSession->createCompileRequest(request.writeRef());

		// Add your Slang source file.
		int translationUnitIndex = request->addTranslationUnit(SLANG_SOURCE_LANGUAGE_SLANG, nullptr);
		request->addTranslationUnitSourceString(translationUnitIndex, "__temp__.slang", sourceCodeStr.c_str());

		// Add target
		int targetIndex = request->addCodeGenTarget(compileTarget);

		// Set profile if it's defiend.
		if (!profile.empty())
		{
			SlangProfileID profileID = _globalSession->findProfile(profile.c_str());
			if (profileID == SLANG_PROFILE_UNKNOWN)
			{
				return SlangCompileResult(false, "", ShaderReflection(), "Failed to find profile: " + profile);
			}
			request->setTargetProfile(targetIndex, profileID); // shader model
		}
		request->addEntryPoint(translationUnitIndex, entryPoint.c_str(), stage); // for VS

		SlangResult res = request->compile();
		if (SLANG_FAILED(res)) {
			std::string error = request->getDiagnosticOutput();
			return SlangCompileResult(false, "", ShaderReflection(), error);
		}

		ComPtr<ISlangBlob> blob;
		request->getEntryPointCodeBlob(0, 0, blob.writeRef());

		std::string code = std::string((const char*)blob->getBufferPointer(), blob->getBufferSize());

		//std::cout << "Compilation succeeded!\n";
		return SlangCompileResult(true, code, ShaderReflection());
	}

	SlangCompileResult SlangSession::compile(
		const std::string& filePath,
		SlangCompileTarget compileTarget,
		const std::string& profile,
		std::vector<SlangStage> stages,
		std::vector<std::string> entryPoints)
	{
		ComPtr<slang::ICompileRequest> request;
		_globalSession->createCompileRequest(request.writeRef());

		// Add your Slang source file.
		int translationUnitIndex = request->addTranslationUnit(SLANG_SOURCE_LANGUAGE_SLANG, nullptr);
		request->addTranslationUnitSourceFile(translationUnitIndex, filePath.c_str());

		// Add target
		int targetIndex = request->addCodeGenTarget(compileTarget);

		// Set profile if it's defiend.
		if (!profile.empty())
		{
			SlangProfileID profileID = _globalSession->findProfile(profile.c_str());
			if (profileID == SLANG_PROFILE_UNKNOWN)
			{
				return SlangCompileResult(false, "", ShaderReflection(), "Failed to find profile: " + profile);
			}
			request->setTargetProfile(targetIndex, profileID); // shader model
		}
		for (size_t i = 0; i < entryPoints.size(); i++)
		{
			request->addEntryPoint(translationUnitIndex, entryPoints[i].c_str(), stages[i]);
		}

		SlangResult res = request->compile();
		if (SLANG_FAILED(res)) {
			std::string error = request->getDiagnosticOutput();
			return SlangCompileResult(false, "", ShaderReflection(), error);
		}

		ComPtr<ISlangBlob> blob;
		request->getEntryPointCodeBlob(0, 0, blob.writeRef());

		std::string code = std::string((const char*)blob->getBufferPointer(), blob->getBufferSize());

		//std::cout << "Compilation succeeded!\n";
		return SlangCompileResult(true, code, ShaderReflection());
	}

	SlangCompileResult SlangSession::compileFromSourceCode(
		const std::string& slangSourceCode,
		SlangCompileTarget compileTarget,
		const std::string& profile,
		std::vector<SlangStage> stages,
		std::vector<std::string> entryPoints)
	{
		ComPtr<slang::ICompileRequest> request;
		_globalSession->createCompileRequest(request.writeRef());

		// Add your Slang source file.
		int translationUnitIndex = request->addTranslationUnit(SLANG_SOURCE_LANGUAGE_SLANG, nullptr);
		request->addTranslationUnitSourceString(translationUnitIndex, "__temp__.slang", slangSourceCode.c_str());

		// Add target
		int targetIndex = request->addCodeGenTarget(compileTarget);
		if (!profile.empty())
		{
			SlangProfileID profileID = _globalSession->findProfile(profile.c_str());
			if (profileID == SLANG_PROFILE_UNKNOWN)
			{
				return SlangCompileResult(false, "", ShaderReflection(), "Failed to find profile: " + profile);
			}
			request->setTargetProfile(targetIndex, profileID); // shader model
		}

		for (size_t i = 0; i < entryPoints.size(); i++)
		{
			request->addEntryPoint(translationUnitIndex, entryPoints[i].c_str(), stages[i]);
		}

		SlangResult res = request->compile();
		if (SLANG_FAILED(res)) {
			std::string error = request->getDiagnosticOutput();
			return SlangCompileResult(false, "", ShaderReflection(), error);
		}

		ComPtr<ISlangBlob> blob;
		request->getEntryPointCodeBlob(0, 0, blob.writeRef());

		std::string code = std::string((const char*)blob->getBufferPointer(), blob->getBufferSize());

		//std::cout << "Compilation succeeded!\n";
		return SlangCompileResult(true, code, ShaderReflection());
	}

	SlangCompileResult SlangSession::compileToGlsl(
		const std::string& filePath,
		ShaderStage stage,
		const std::string& entryPoint,
		GlslProfile profile)
	{
		SlangStage slangStage = shaderStageMap[stage];
		std::string glslProfile = glslProfileMap[profile];

		return compile(
			filePath,
			SLANG_GLSL,
			glslProfile,
			slangStage,
			entryPoint
		);
	}

	SlangCompileResult SlangSession::compileSourceCodeToGlsl(
		const std::string& slangSourceCode,
		ShaderStage stage,
		const std::string& entryPoint,
		GlslProfile profile)
	{
		SlangStage slangStage = shaderStageMap[stage];
		std::string glslProfile = glslProfileMap[profile];

		return compileFromSourceCode(
			slangSourceCode,
			SLANG_GLSL,
			glslProfile,
			slangStage,
			entryPoint
		);
	}

	SlangCompileResult SlangSession::compileToHlsl(
		const std::string& filePath,
		ShaderStage stage,
		const std::string& entryPoint,
		HlslProfile profile)
	{
		SlangStage slangStage = shaderStageMap[stage];
		std::string hlslProfile = hlslProfileMap[profile];

		return compile(
			filePath,
			SLANG_HLSL,
			hlslProfile,
			slangStage,
			entryPoint
		);
	}

	SlangCompileResult SlangSession::compileToMetal(
		const std::string& filePath,
		ShaderStage stage,
		const std::string& entryPoint,
		MetalProfile profile)
	{
		SlangStage slangStage = shaderStageMap[stage];
		std::string metalProfile = metalProfileMap[profile];

		return compile(
			filePath,
			SLANG_METAL,
			metalProfile,
			slangStage,
			entryPoint
		);
	}
	SlangCompileResult SlangSession::compileToMetal(
		const std::string& filePath,
		std::vector<ShaderStage> stages,
		std::vector<std::string> entryPoints,
		MetalProfile profile)
	{
		std::vector<SlangStage> slangStages;
		for (const auto& stage : stages)
		{
			slangStages.push_back(shaderStageMap[stage]);
		}

		std::string metalProfile = metalProfileMap[profile];

		return compile(
			filePath,
			SLANG_METAL,
			metalProfile,
			slangStages,
			entryPoints
		);
	}

	SlangCompileResult SlangSession::compileToWgsl(
		const std::string& filePath,
		ShaderStage stage,
		const std::string& entryPoint)
	{
		SlangStage slangStage = shaderStageMap[stage];

		return compile(
			filePath,
			SLANG_WGSL,
			"",
			slangStage,
			entryPoint
		);
	}

	SlangCompileResult SlangSession::compileToWgsl(
		const std::string& filePath,
		std::vector<ShaderStage> stages,
		std::vector<std::string> entryPoints)
	{
		std::vector<SlangStage> slangStages;
		for (const auto& stage : stages)
		{
			slangStages.push_back(shaderStageMap[stage]);
		}

		return compile(
			filePath,
			SLANG_METAL,
			"",
			slangStages,
			entryPoints
		);
	}

        SlangCompileResult SlangSession::compileSourceCodeToWgsl(
			const std::string& slangSourceCode,
			std::vector<ShaderStage> stages,
			std::vector<std::string> entryPoints
        ) {

          std::vector<SlangStage> slangStages;
		for (const auto& stage : stages)
		{
			slangStages.push_back(shaderStageMap[stage]);
		}

		return compileFromSourceCode(
			slangSourceCode,
			SLANG_WGSL,
			"",
			slangStages,
			entryPoints
		);
          }

	SlangCompileResult SlangSession::compileToSpirV(
		const std::string& filePath,
		std::vector<ShaderStage> stages,
		std::vector<std::string> entryPoints,
		SpirVProfile profile
	)
	{
		std::vector<SlangStage> slangStages;
		for (const auto& stage : stages)
		{
			slangStages.push_back(shaderStageMap[stage]);
		}

		std::string metalProfile = spirvProfileMap[profile];

		return compile(
			filePath,
			SLANG_SPIRV,
			"spirv_1_0",
			slangStages,
			entryPoints
		);
	}

	SlangCompileResult SlangSession::compileSourceCodeToSpirV(
		const std::string& slangSourceCode,
		std::vector<ShaderStage> stages,
		std::vector<std::string> entryPoints,
		SpirVProfile profile
	)
	{
		std::vector<SlangStage> slangStages;
		for (const auto& stage : stages)
		{
			slangStages.push_back(shaderStageMap[stage]);
		}

		std::string metalProfile = spirvProfileMap[profile];

		return compileFromSourceCode(
			slangSourceCode,
			SLANG_SPIRV,
			"spirv_1_0",
			slangStages,
			entryPoints
		);

	}
}