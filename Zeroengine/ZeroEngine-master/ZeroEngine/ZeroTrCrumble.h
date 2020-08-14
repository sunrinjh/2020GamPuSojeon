#pragma once
#include "ZeroIShader.h"

class ZeroTrCrumble : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 m_pCloudTex;
	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrCrumble(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrCrumble();

	void Update(float _eTime);
};
