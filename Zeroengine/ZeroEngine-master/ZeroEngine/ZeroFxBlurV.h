#pragma once

#include "ZeroIShader.h"

class ZeroFxBlurV : public ZeroIShader {
private:
	float time;
	float beginTime;
	float blur;

public:
	ZeroFxBlurV(float _time, char* _renderPage);
	~ZeroFxBlurV();

	void Update(float _eTime);
};
