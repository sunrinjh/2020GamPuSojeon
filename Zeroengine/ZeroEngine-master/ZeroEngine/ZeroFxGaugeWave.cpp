#include "stdafx.h"
#include "ZeroFxGaugeWave.h"

ZeroFxGaugeWave::ZeroFxGaugeWave(char* renderpage)
    : ZeroIShader(renderpage), m_fPower(100), m_bShock(false), m_fShock(0.0f), m_fShockFrame(0.0f) {
	if (!ZeroRTMgr(renderPage)->Shader())
		ZeroRTMgr(renderPage)->SetShader("Texture/Shader/GaugeWave.fx");
	else {
		SetErase(true);
		SetRightErase(true);
	}
}
ZeroFxGaugeWave::~ZeroFxGaugeWave() {}

void ZeroFxGaugeWave::Update(float eTime) {
	ZeroIShader::Update(eTime);
	if (IsRightErase()) return;

	if (m_bShock) {
		m_bShock = false;
		m_fShock = 1.0f;
		m_fShockFrame = 0.0f;
	}
	if (m_fShock >= 0) {
		m_fPower = 100 - m_fShock * 50 * ZeroMathMgr->Sin(1000 * m_fShockFrame);
		m_fShock -= eTime;
		m_fShockFrame += eTime;
	}
	else {
		m_fPower = 100.0f;
	}

	if (ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->Shader()->SetFloat("STRENGTH", m_fPower);
		ZeroRTMgr(renderPage)->Shader()->SetFloat("CURRENT_TIME", StartToCurrentTime());
	}
}
