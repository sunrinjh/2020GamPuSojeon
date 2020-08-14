#pragma once
#include "ZeroIShader.h"

class ZeroTrSaturate : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrSaturate(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrSaturate();

	void Update(float _eTime);
};
