#pragma once
#include "ZeroIShader.h"

class ZeroFxGaugeWave : public ZeroIShader {
private:
	float m_fPower;

	bool m_bShock;
	float m_fShock;
	float m_fShockFrame;

public:
	ZeroFxGaugeWave(char* renderpage);
	~ZeroFxGaugeWave();

	void Update(float eTime);
	void SetShock(bool shock) {
		m_bShock = shock;
	}
};
