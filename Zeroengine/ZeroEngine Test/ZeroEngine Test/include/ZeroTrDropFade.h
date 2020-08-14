#pragma once
#include "ZeroIShader.h"

class ZeroTrDropFade : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 m_pCloudTex;
	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrDropFade(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrDropFade();

	void Update(float _eTime);
};
