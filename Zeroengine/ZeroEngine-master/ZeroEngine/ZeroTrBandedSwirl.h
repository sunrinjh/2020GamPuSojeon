#pragma once
#include "ZeroIShader.h"

class ZeroTrBandedSwirl : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrBandedSwirl(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrBandedSwirl();

	void Update(float _eTime);
};
