#include "stdafx.h"
#include "ZeroTextureManager.h"
#include "ZeroApplication.h"

ZeroTextureManager::ZeroTextureManager() {}

ZeroTextureManager::~ZeroTextureManager() {
	Clear();
}

ZeroTextureManager* ZeroTextureManager::Instance() {
	static ZeroTextureManager instance;
	return &instance;
}

void ZeroTextureManager::ReloadResource() {
	for (TEXTURE::iterator iter = textureList.begin(); iter != textureList.end(); iter++) {
		iter->second->Release();
		D3DXCreateTextureFromFileExA(ZeroApp->GetDevice(), iter->first.c_str(),
		                             D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 1, 0,
		                             D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
		                             NULL, NULL, NULL, &iter->second);
	}
}

LPDIRECT3DTEXTURE9 ZeroTextureManager::LoadTextureFromFile(const char* _path) {
	if (textureList[_path] != NULL) return textureList[_path];

	D3DXCreateTextureFromFileExA(ZeroApp->GetDevice(), _path, D3DX_DEFAULT_NONPOW2,
	                             D3DX_DEFAULT_NONPOW2, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
	                             D3DX_DEFAULT, D3DX_DEFAULT, NULL, NULL, NULL, &textureList[_path]);

	return textureList[_path];
}

void ZeroTextureManager::Release(const char* _path, ...) {
	char buffer[256] = { 0 };
	char* data = buffer;
	va_list vargs;
	va_start(vargs, _path);
	int ret = vsnprintf(data, sizeof(buffer), _path, vargs);
	va_end(vargs);
	if (ret + 1 > sizeof(buffer)) data = static_cast<char*>(malloc(ret + 1));
	va_start(vargs, _path);
	vsprintf(data, _path, vargs);
	va_end(vargs);

	TEXTURE::iterator iter = textureList.find(data);
	if (iter != textureList.end()) {
		SAFE_RELEASE(iter->second);
		textureList.erase(iter);
	}

	if (data != buffer) free(data);
}

void ZeroTextureManager::Clear() {
	for (TEXTURE::iterator iter = textureList.begin(); iter != textureList.end(); iter++) {
		SAFE_RELEASE(iter->second);
	}
	textureList.clear();
}
