#pragma once
#include "ZeroIShader.h"

class ZeroFxRadialBlur : public ZeroIShader {
private:
	float time;
	float beginTime;
	float power;

	D3DXVECTOR4 center;
	float blurStart;
	float blurWidth;

public:
	ZeroFxRadialBlur(float _time, float _power_0_1, char* _renderPage);
	~ZeroFxRadialBlur();

	void Update(float _eTime);

	void SetCenter(float x, float y) {
		center.x = x;
		center.y = y;
	}
};
