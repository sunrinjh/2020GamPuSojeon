#pragma once
#include "ZeroIShader.h"

class ZeroTrSmoothSwirlGrid : public ZeroIShader {
private:
	float time;
	float beginTime;

	LPDIRECT3DTEXTURE9 secondTexture;

public:
	ZeroTrSmoothSwirlGrid(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture);
	~ZeroTrSmoothSwirlGrid();

	void Update(float _eTime);
};
