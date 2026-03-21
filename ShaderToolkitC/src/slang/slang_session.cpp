#include "slang/slang_session.hpp"
#include <spdlog/spdlog.h>
#include <string>

namespace ris_shader_toolkit {
	SlangSession::SlangSession()
	{
		_shaderStageMap = {
			{ ShaderStage::Vertex, SLANG_STAGE_VERTEX },
			{ ShaderStage::Fragment, SLANG_STAGE_FRAGMENT },
			{ ShaderStage::Compute, SLANG_STAGE_COMPUTE },
			//{ ShaderStage::Geometry, SLANG_STAGE_GEOMETRY },
			//{ ShaderStage::Hull, SLANG_STAGE_HULL },
			//{ ShaderStage::Domain, SLANG_STAGE_DOMAIN }
		};

		_shaderAttributeValueToSlangStageMap = {
			{ "vertex", SLANG_STAGE_VERTEX },
			{ "fragment", SLANG_STAGE_FRAGMENT },
			{ "compute", SLANG_STAGE_COMPUTE },
		};

		_hlslProfileMap = {
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

		_glslProfileMap = {
			{ GlslProfile::GLSL_330, "glsl_330" },
			{ GlslProfile::GLSL_400, "glsl_400" },
			{ GlslProfile::GLSL_410, "glsl_410" },
			{ GlslProfile::GLSL_420, "glsl_420" },
			{ GlslProfile::GLSL_430, "glsl_430" },
			{ GlslProfile::GLSL_440, "glsl_440" },
			{ GlslProfile::GLSL_450, "glsl_450" },
			{ GlslProfile::GLSL_460, "glsl_460" },
		};

		_metalProfileMap = {
			{ MetalProfile::MSL_1_0, "metallib_1_0" },
			{ MetalProfile::MSL_1_1, "metallib_1_1" },
			{ MetalProfile::MSL_1_2, "metallib_1_2" },
			{ MetalProfile::MSL_2_0, "metallib_2_0" },
			{ MetalProfile::MSL_2_1, "metallib_2_1" },
			{ MetalProfile::MSL_2_2, "metallib_2_2" },
			{ MetalProfile::MSL_2_3, "metallib_2_3" },
			{ MetalProfile::MSL_2_4, "metallib_2_4" }
		};

		_spirvProfileMap = {
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

	std::string SlangSession::readCompiledCode(ComPtr<slang::IComponentType> component, size_t entryPointCount)
	{
		std::string finalCode;
		for (size_t i = 0; i < entryPointCount; i++)
		{
			ComPtr<slang::IBlob> shaderBlob = nullptr;
			ComPtr<slang::IBlob> diagnosticBlob = nullptr;
			SlangResult result = component->getEntryPointCode(i, 0, shaderBlob.writeRef(), diagnosticBlob.writeRef());
			if (SLANG_SUCCEEDED(result)) {
				std::string code = std::string((const char*)shaderBlob->getBufferPointer(), shaderBlob->getBufferSize());
				finalCode += code + "\n";
			}
			else {
				std::string error = diagnosticBlob ? std::string((const char*)diagnosticBlob->getBufferPointer(), diagnosticBlob->getBufferSize()) : "Unknown error";
				spdlog::error("Failed to get compiled code for entry point index {}. {}", i, error);
			}
		}
		return finalCode;
	}


	std::vector<uint32_t> SlangSession::readCompiledBinaryCode(ComPtr<slang::IComponentType> component)
	{
		std::vector<uint32_t> finalCode;

		ComPtr<slang::IBlob> shaderBlob = nullptr;
		ComPtr<slang::IBlob> diagnosticBlob = nullptr;
		SlangResult result = component->getTargetCode(0, shaderBlob.writeRef(), diagnosticBlob.writeRef());

		if (SLANG_SUCCEEDED(result))
		{
			auto* data = reinterpret_cast<const uint32_t*>(shaderBlob->getBufferPointer());
			size_t wordCount = shaderBlob->getBufferSize() / sizeof(uint32_t);

			for (size_t j = 0; j < wordCount; j++)
			{
				finalCode.push_back(data[j]);
			}
		}
		else
		{
			std::string error = diagnosticBlob ? std::string((const char*)diagnosticBlob->getBufferPointer(), diagnosticBlob->getBufferSize()) : "Unknown error";
			spdlog::error("Failed to get compiled code. {}", error);
		}

		return finalCode;
	}

	SlangCompileResult SlangSession::compile(
		const std::string& sourceCode,
		SlangCompileTarget compileTarget,
		std::string profile,
		const std::vector<SlangStage> stages,
		const std::vector<std::string> entryPoints
	) {
		// 1. CREATE A SLANG SESSION
		slang::TargetDesc targetDesc;
		targetDesc.format = compileTarget;

		slang::SessionDesc sessionDesc;
		sessionDesc.targets = &targetDesc;
		sessionDesc.targetCount = 1;
	/*	sessionDesc.defaultMatrixLayoutMode = SLANG_MATRIX_LAYOUT_COLUMN_MAJOR;
		sessionDesc.allowGLSLSyntax = true;*/

		if (!profile.empty())
		{
			SlangProfileID profileID = _globalSession->findProfile(profile.c_str());
			if (profileID == SLANG_PROFILE_UNKNOWN)
			{
				return SlangCompileResult(false, "", ShaderReflection(), "Failed to find profile: " + profile);
			}
			targetDesc.profile = profileID;
		}

		ComPtr<slang::ISession> session;
		_globalSession->createSession(sessionDesc, session.writeRef());

		std::vector<slang::IComponentType*> componentTypes;


		// 2. CREATE A MODULE FROM SOURCE CODE
		// This loads the Slang source code into a module, which can then be compiled. 
		// The module represents the entire shader program, including all entry points and shared code.
		ComPtr<slang::IBlob> diagnosticBlob = nullptr;
		// Note that module parameter and path parameter are not relevant when compiling from source code.
		slang::IModule* module = session->loadModuleFromSourceString(
			"__temp__",
			"__temp__.slang",
			sourceCode.c_str(),
			diagnosticBlob.writeRef());

		if (!module)
		{
			if (diagnosticBlob.readRef())
			{
				std::string error = std::string((const char*)diagnosticBlob->getBufferPointer(), diagnosticBlob->getBufferSize());
				return SlangCompileResult(false, "", ShaderReflection(), error);
			}
			else
			{
				return SlangCompileResult(false, "", ShaderReflection(), "Failed to load module from source string, and no diagnostics available.");
			}
		}
		componentTypes.push_back(module);

		// 3. LOOK UP ENTRY POINTS AND COMPILE

		// If we have entry points, we will use that to read, otherwise we will simply lookup vertex stages.
		std::vector<ComPtr<slang::IEntryPoint> > entryPointInterfaces;
		if (entryPoints.size() > 0)
		{
			for (size_t i = 0; i < entryPoints.size(); i++)
			{
				std::string main = entryPoints[i];
				ComPtr<slang::IEntryPoint> entryPoint = nullptr;
				SlangResult result = module->findEntryPointByName(main.c_str(), entryPoint.writeRef());
				if (SLANG_FAILED(result))
				{
					if (diagnosticBlob)
					{
						std::string error = std::string((const char*)diagnosticBlob->getBufferPointer(), diagnosticBlob->getBufferSize());
						return SlangCompileResult(false, "", ShaderReflection(), "Failed to find entry point: " + entryPoints[i] + ". " + error);
					}
					else
					{
						return SlangCompileResult(false, "", ShaderReflection(), "Failed to find entry point: " + entryPoints[i] + ". No diagnostics available.");
					}
				}
				entryPointInterfaces.push_back(entryPoint);
				componentTypes.push_back(entryPoint.get());
			}
		}
		// If we do not specify entry points, we will look up entry points based on stages.
		// This requires the Slang source code to be decorated with @shader attributes to specify the stage for each entry point.
		else
		{

			auto entryPointCount = module->getDefinedEntryPointCount();

			for (size_t i = 0; i < entryPointCount; i++)
			{
				ComPtr<slang::IEntryPoint> entryPoint = nullptr;
				SlangResult result = module->getDefinedEntryPoint(i, entryPoint.writeRef());

				if (SLANG_FAILED(result))
				{
					if (diagnosticBlob)
					{
						std::string error = std::string((const char*)diagnosticBlob->getBufferPointer(), diagnosticBlob->getBufferSize());
						return SlangCompileResult::errorResult("Failed to find entry point by index: " + std::to_string(i) + ". " + error);
					}
					else
					{
						return SlangCompileResult::errorResult("Failed to find entry point: by index" + std::to_string(i) + ". No diagnostics available.");
					}
				}

				auto slangStage = findEntryPointStage(entryPoint);

				if (slangStage == std::nullopt)
				{
					std::string error = "Unable to find entry point stage.";
					return SlangCompileResult::errorResult(error);
				}

				for (size_t i = 0; i < stages.size(); i++)
				{
					if (stages[i] == slangStage)
					{
						entryPointInterfaces.push_back(entryPoint);
						componentTypes.push_back(entryPoint.get());
					}
				}
			}

			if (entryPointInterfaces.size() == 0)
			{
				std::string error = "Unable to find entry point.";
				return SlangCompileResult::errorResult(error);
			}
		}


		// 4. CREATE A COMPOSITE COMPONENT TYPE
		// Link the module to a composite component type, which represents the final shader program that can be executed.
		ComPtr<slang::IComponentType> program;
		SlangResult result = session->createCompositeComponentType(
			componentTypes.data(),
			componentTypes.size(),
			program.writeRef(),
			diagnosticBlob.writeRef()
		);

		if (SLANG_FAILED(result))
		{
			std::string error = std::string((const char*)diagnosticBlob->getBufferPointer(), diagnosticBlob->getBufferSize());
			return SlangCompileResult(false, "", ShaderReflection(), error);
		}

		size_t entryPointCount = entryPoints.size() == 0 ? stages.size() : entryPoints.size();

		// BINARY FORMATS
		if (compileTarget == SlangCompileTarget::SLANG_SPIRV)
		{
			// We can read multiple binary entry points, but for SPIR-V we only 
			// ever support single entry point, so we will just read the first one.
			auto binary = readCompiledBinaryCode(program);
			return SlangCompileResult(true, binary, ShaderReflection());
		}
		else
		{
			// Get entry points.
			std::string code = readCompiledCode(program, entryPointCount);
			return SlangCompileResult(true, code, ShaderReflection());
		}
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

	std::optional<SlangStage> SlangSession::findEntryPointStage(ComPtr<slang::IEntryPoint> entryPoint)
	{
		auto functionReflection = entryPoint->getFunctionReflection();

		if (functionReflection == nullptr)
		{
			spdlog::error("Failed to get function reflection for entry point.");
			return std::nullopt;
		}

		// We need to check if entry point has a "shader" attribute for example, [shader("vertex")] VSOutput main_vs(VSInput input)
		auto shaderAttr = functionReflection->findAttributeByName(_globalSession.get(), "shader");

		if (shaderAttr == nullptr)
		{
			spdlog::error("Failed to find 'shader' attribute.");
			return std::nullopt;
		}

		// shader attribute will contain value such as "vertex" eg. shader("vertex")
		size_t nameLength = 0;
		auto nameStr = shaderAttr->getArgumentValueString(0, &nameLength);

		if (nameLength == 0)
		{
			spdlog::error("Failed to retrieve 'shader' attribute argument value.");
			return std::nullopt;
		}

		return _shaderAttributeValueToSlangStageMap[nameStr];
	}

	/*

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
			{ slangStage },
			{ entryPoint }
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
			{ slangStage },
			{ entryPoint }
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
			{ slangStages },
			{ entryPoints }
		);
	}*/

	SlangCompileResult SlangSession::compileToWgsl(
		const std::string& sourceCode,
		const std::vector<ShaderStage> stages,
		const std::vector<std::string> entryPoints)
	{
		std::vector<SlangStage> slangStages;
		for (const auto& stage : stages)
		{
			slangStages.push_back(_shaderStageMap[stage]);
		}

		return compile(
			sourceCode,
			SLANG_WGSL,
			"",
			slangStages,
			entryPoints
		);
	}

	SlangCompileResult SlangSession::compileToSpirV(
		const std::string& sourceCode,
		std::vector<ShaderStage> stages,
		std::vector<std::string> entryPoints,
		SpirVProfile profile
	)
	{
		std::vector<SlangStage> slangStages;
		for (const auto& stage : stages)
		{
			slangStages.push_back(_shaderStageMap[stage]);
		}

		std::string spirVProfile = _spirvProfileMap[profile];

		return compile(
			sourceCode,
			SLANG_SPIRV,
			spirVProfile,
			slangStages,
			entryPoints
		);
	}

	SlangCompileResult SlangSession::compileToGlsl(
		const std::string& sourceCode,
		ShaderStage stages,
		std::string entryPoint,
		GlslProfile profile) {

		SlangStage slangStage = _shaderStageMap[stages];
		std::string glslProfile = _glslProfileMap[profile];

		std::vector<std::string> entryPoints;
		if (!entryPoint.empty())
		{
			entryPoints.push_back(entryPoint);
		}

		return compile(
			sourceCode,
			SLANG_GLSL,
			glslProfile,
			{ slangStage },
			entryPoints
		);

	}
}