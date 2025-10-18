//
// Created by Erkapic Luka on 27.9.2025.
//

#include "slang/slang_session.hpp"
#include <string>

namespace shader_toolkit {
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

		metalProfileMap = {
			{ MetalProfile::MSL_1_0, "metal1.0" },
			{ MetalProfile::MSL_1_1, "metal1.1" },
			{ MetalProfile::MSL_1_2, "metal1.2" },
			{ MetalProfile::MSL_2_0, "metal2.0" },
			{ MetalProfile::MSL_2_1, "metal2.1" },
			{ MetalProfile::MSL_2_2, "metal2.2" },
			{ MetalProfile::MSL_3_0, "metal3.0" },
		};
	}

	bool SlangSession::initialize() {
		// First we need to create slang global session with work with the Slang API.
		SlangResult res = slang::createGlobalSession(session.writeRef());
		if (SLANG_FAILED(res))
		{
			// Print error.
			return false;
		}

		return true;
	}

	SlangCompileResult SlangSession::compile(
		const std::string& filePath,
		SlangCompileTarget compileTarget,
		const std::string& profile,
		SlangStage stage,
		const std::string& entryPoint)
	{
		ComPtr<slang::ICompileRequest> request;
		session->createCompileRequest(request.writeRef());

		// Add your Slang source file.
		int translationUnitIndex = request->addTranslationUnit(SLANG_SOURCE_LANGUAGE_SLANG, nullptr);
		request->addTranslationUnitSourceFile(translationUnitIndex, filePath.c_str());

		// Add target
		int targetIndex = request->addCodeGenTarget(compileTarget);
		request->setTargetProfile(targetIndex, session->findProfile(profile.c_str())); // shader model

		request->addEntryPoint(translationUnitIndex, entryPoint.c_str(), stage); // for VS

		SlangResult res = request->compile();
		if (SLANG_FAILED(res)) {
			std::string error = request->getDiagnosticOutput();
			return SlangCompileResult(false, "", error);
		}

		ComPtr<ISlangBlob> blob;
		request->getEntryPointCodeBlob(0, 0, blob.writeRef());

		std::string code = std::string((const char*)blob->getBufferPointer(), blob->getBufferSize());

		//std::cout << "Compilation succeeded!\n";
		return SlangCompileResult(true, code);
	}

	SlangCompileResult SlangSession::compile(
		const std::string& filePath,
		SlangCompileTarget compileTarget,
		const std::string& profile,
		std::vector<SlangStage> stages,
		std::vector<std::string> entryPoints)
	{
		ComPtr<slang::ICompileRequest> request;
		session->createCompileRequest(request.writeRef());

		// Add your Slang source file.
		int translationUnitIndex = request->addTranslationUnit(SLANG_SOURCE_LANGUAGE_SLANG, nullptr);
		request->addTranslationUnitSourceFile(translationUnitIndex, filePath.c_str());

		// Add target
		int targetIndex = request->addCodeGenTarget(compileTarget);
		request->setTargetProfile(targetIndex, session->findProfile(profile.c_str())); // shader model

		for (size_t i = 0; i < stages.size(); i++) 
		{
			request->addEntryPoint(translationUnitIndex, entryPoints[i].c_str(), stages[i]); 
		}

		SlangResult res = request->compile();
		if (SLANG_FAILED(res)) {
			std::string error = request->getDiagnosticOutput();
			return SlangCompileResult(false, "", error);
		}

		ComPtr<ISlangBlob> blob;
		request->getEntryPointCodeBlob(0, 0, blob.writeRef());

		std::string code = std::string((const char*)blob->getBufferPointer(), blob->getBufferSize());

		//std::cout << "Compilation succeeded!\n";
		return SlangCompileResult(true, code);
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
}