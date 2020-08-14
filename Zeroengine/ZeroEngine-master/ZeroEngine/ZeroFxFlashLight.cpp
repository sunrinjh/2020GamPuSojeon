#include "stdafx.h"
#include "ZeroFxFlashLight.h"

ZeroFxFlashLight::ZeroFxFlashLight(float time, char* renderpage)
    : ZeroIShader(renderpage), m_fTime(time), m_fBeginTime(time) {
	if (!ZeroRTMgr(renderPage)->Shader())
		ZeroRTMgr(renderPage)->SetShader("Texture/Shader/FlashLight.fx");
	else {
		SetErase(true);
		SetRightErase(true);
	}
}
ZeroFxFlashLight::~ZeroFxFlashLight() {}

void ZeroFxFlashLight::Update(float eTime) {
	ZeroIShader::Update(eTime);
	if (IsRightErase()) return;

	m_fTime -= eTime;

	if (m_fTime <= 0) {
		SetErase(true);
		ZeroRTMgr(renderPage)->ClearShader();
	}
}
