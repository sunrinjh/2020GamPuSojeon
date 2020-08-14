#pragma once
#include "ZeroIShader.h"

class ZeroTrRadialBlur : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrRadialBlur(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrRadialBlur();

	void Update(float _eTime);
};
