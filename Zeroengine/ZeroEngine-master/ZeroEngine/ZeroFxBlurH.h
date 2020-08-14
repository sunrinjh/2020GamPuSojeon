#pragma once

#include "ZeroIShader.h"

class ZeroFxBlurH : public ZeroIShader {
private:
	float time;
	float beginTime;
	float blur;

public:
	ZeroFxBlurH(float _time, char* _renderPage);
	~ZeroFxBlurH();

	void Update(float _eTime);
};
