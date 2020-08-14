#pragma once
#include "ZeroIShader.h"

class ZeroTrCircleStretch : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrCircleStretch(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrCircleStretch();

	void Update(float _eTime);
};
