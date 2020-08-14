#pragma once
#include "ZeroIShader.h"

class ZeroFxFlashLight : public ZeroIShader {
private:
	float m_fTime;
	float m_fBeginTime;

public:
	ZeroFxFlashLight(float time, char* renderpage);
	~ZeroFxFlashLight();

	void Update(float eTime);
};
