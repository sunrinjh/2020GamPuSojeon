#pragma once
#include "ZeroIShader.h"

class ZeroTrRandomCircleReveal : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 m_pCloudTex;
	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrRandomCircleReveal(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrRandomCircleReveal();

	void Update(float _eTime);
};
