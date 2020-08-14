#pragma once
#include "ZeroIShader.h"

class ZeroTrFade : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrFade(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrFade();

	void Update(float _eTime);
};
