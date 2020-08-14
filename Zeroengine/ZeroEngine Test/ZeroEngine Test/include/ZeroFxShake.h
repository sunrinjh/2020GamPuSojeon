#pragma once

#include "ZeroIShader.h"

class ZeroFxShake : public ZeroIShader {
private:
	float strength;
	float time;
	float beginTime;

public:
	ZeroFxShake(float _power_0_0p25, float _time, char* _renderPage);
	~ZeroFxShake();

	void Update(float _eTime);
};
