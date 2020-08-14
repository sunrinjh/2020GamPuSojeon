#pragma once
#include "ZeroIShader.h"

class ZeroTrPixelate : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrPixelate(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrPixelate();

	void Update(float _eTime);
};
