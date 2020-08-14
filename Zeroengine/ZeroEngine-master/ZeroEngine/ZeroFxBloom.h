#pragma once
#include "ZeroIShader.h"

class ZeroFxBloom : public ZeroIShader {
private:
	float m_fTime;
	float m_fBeginTime;

	float m_fBlur;

public:
	ZeroFxBloom(float time, char* renderpage);
	~ZeroFxBloom();

	void Update(float eTime);
};
