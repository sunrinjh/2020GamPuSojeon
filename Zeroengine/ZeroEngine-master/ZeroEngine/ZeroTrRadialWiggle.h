#pragma once
#include "ZeroIShader.h"

class ZeroTrRadialWiggle : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 m_pCloudTex;
	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrRadialWiggle(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrRadialWiggle();

	void Update(float _eTime);
};
