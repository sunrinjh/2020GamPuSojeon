#pragma once

#include "ZeroIShader.h"

class ZeroFxEdgeDetect : public ZeroIShader {
private:
	float time;
	float beginTime;

public:
	ZeroFxEdgeDetect(float _time, char* _renderPage);
	~ZeroFxEdgeDetect();

	void Update(float _eTime);
};
