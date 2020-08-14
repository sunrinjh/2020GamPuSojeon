#pragma once

#include "ZeroIShader.h"
#include "ZeroResource.h"

class ZeroFxNightVision : public ZeroIShader, public ZeroResource {
private:
	LPDIRECT3DTEXTURE9 texNoise;
	float time;
	float beginTime;

	// 경과 시간
	float elapsedTime;

	void ReloadResource();

public:
	ZeroFxNightVision(float _time, char* _renderPage);
	~ZeroFxNightVision();

	void Update(float _eTime);
};
