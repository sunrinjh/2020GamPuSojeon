#include "stdafx.h"
#include "ZeroFxWaveFade.h"

ZeroFxWaveFade::ZeroFxWaveFade(float time, float power_0_1, float speed_0_1, char* renderpage)
    : ZeroIShader(renderpage),
      m_fTime(time),
      m_fBeginTime(time),
      m_fPower(power_0_1 + 1.0f),
      m_fSpeed(speed_0_1) {
	if (!ZeroRTMgr(renderPage)->Shader())
		ZeroRTMgr(renderPage)->SetShader("Texture/Shader/WaveFade.fx");
	else {
		SetErase(true);
		SetRightErase(true);
	}

	ZeroMathMgr->Clamp(m_fPower, 1.0, 2.0);
	ZeroMathMgr->Clamp(m_fSpeed, 0, 2);
}
ZeroFxWaveFade::~ZeroFxWaveFade() {}

void ZeroFxWaveFade::Update(float eTime) {
	ZeroIShader::Update(eTime);
	if (IsRightErase()) return;

	m_fTime -= eTime;

	float power = m_fPower * 200.0f *
	              (pow(ZeroMathMgr->Sin(180.0f * (m_fBeginTime - m_fTime) / m_fBeginTime), 4.0f));
	// ZeroMathMgr->Clamp(power,0,200);

	if (ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->Shader()->SetFloat("STRENGTH", power);
		ZeroRTMgr(renderPage)->Shader()->SetFloat("CURRENT_TIME", StartToCurrentTime());
		ZeroRTMgr(renderPage)->Shader()->SetFloat("SPEED", m_fSpeed);
	}

	if (m_fTime <= 0) {
		SetErase(true);
		ZeroRTMgr(renderPage)->ClearShader();
	}
}
