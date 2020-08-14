#pragma once
#include "ZeroIShader.h"

class ZeroTrCloudReveal : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 m_pCloudTex;
	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrCloudReveal(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrCloudReveal();

	void Update(float _eTime);
};
