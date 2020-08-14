#pragma once
#include "ZeroIShader.h"

class ZeroTrRotateCrumble : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 m_pCloudTex;
	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrRotateCrumble(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrRotateCrumble();

	void Update(float _eTime);
};
