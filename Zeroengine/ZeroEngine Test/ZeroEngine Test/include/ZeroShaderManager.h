#pragma once

using namespace std;

#define ZeroShaderMgr ZeroShaderManager::Instance()

class ZeroShaderManager {
private:
	ZeroShaderManager();

	typedef map<const char*, LPD3DXEFFECT> SHADER;
	SHADER shaderList;

public:
	~ZeroShaderManager();

	static ZeroShaderManager* Instance();

	LPD3DXEFFECT LoadShaderFromFile(const char* _path);
	void ReloadResource();
};
