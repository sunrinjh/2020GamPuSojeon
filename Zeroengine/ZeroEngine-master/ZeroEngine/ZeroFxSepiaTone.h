#pragma once

#include "ZeroIShader.h"

class ZeroFxSepiaTone : public ZeroIShader {
private:
	float time;
	float beginTime;

public:
	ZeroFxSepiaTone(float _time, char* _renderPage);
	~ZeroFxSepiaTone();

	void Update(float _eTime);
};
