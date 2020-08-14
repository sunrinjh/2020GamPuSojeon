#pragma once
#include "ZeroIShader.h"

class ZeroFxWaveFade : public ZeroIShader {
private:
	float m_fTime;
	float m_fBeginTime;
	float m_fPower;
	float m_fSpeed;

public:
	ZeroFxWaveFade(float time, float power_0_1, float speed_0_2, char* renderpage);
	~ZeroFxWaveFade();

	void Update(float eTime);
};
