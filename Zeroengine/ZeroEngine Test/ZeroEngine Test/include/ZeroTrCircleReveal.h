#pragma once
#include "ZeroIShader.h"

class ZeroTrCircleReveal : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrCircleReveal(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrCircleReveal();

	void Update(float _eTime);
};
