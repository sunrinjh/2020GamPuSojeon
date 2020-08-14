#pragma once
#include "ZeroIShader.h"

class ZeroTrSlideIn : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrSlideIn(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrSlideIn();

	void Update(float _eTime);
};
