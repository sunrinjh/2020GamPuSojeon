#include "stdafx.h"
#include "ZeroShaderManager.h"
#include "ZeroApplication.h"

ZeroShaderManager::ZeroShaderManager() {}

ZeroShaderManager::~ZeroShaderManager() {
	for (SHADER::iterator iter = shaderList.begin(); iter != shaderList.end(); ++iter) {
		SAFE_RELEASE(iter->second);
	}
	shaderList.clear();
}

ZeroShaderManager* ZeroShaderManager::Instance() {
	static ZeroShaderManager instance;
	return &instance;
}

LPD3DXEFFECT ZeroShaderManager::LoadShaderFromFile(const char* _path) {
	if (shaderList[_path] != NULL) return shaderList[_path];

	D3DXCreateEffectFromFileA(ZeroApp->GetDevice(), _path, NULL, NULL,
	                          D3DXSHADER_USE_LEGACY_D3DX9_31_DLL, NULL, &shaderList[_path], NULL);

	return shaderList[_path];
}

void ZeroShaderManager::ReloadResource() {
	for (SHADER::iterator iter = shaderList.begin(); iter != shaderList.end(); iter++) {
		iter->second->Release();

		D3DXCreateEffectFromFileA(ZeroApp->GetDevice(), iter->first, NULL, NULL,
		                          D3DXSHADER_USE_LEGACY_D3DX9_31_DLL, NULL,
		                          &shaderList[iter->first], NULL);
	}
}
