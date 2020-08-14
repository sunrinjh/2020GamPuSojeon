#pragma once
#include "ZeroIShader.h"

class ZeroTrRipple : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrRipple(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrRipple();

	void Update(float _eTime);
};
