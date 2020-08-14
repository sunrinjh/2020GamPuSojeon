#pragma once

#include "ZeroIShader.h"

class ZeroFxGrayTone : public ZeroIShader {
private:
	float time;
	float beginTime;

public:
	ZeroFxGrayTone(float _time, char* _renderPage);
	~ZeroFxGrayTone();

	void Update(float _eTime);
};
