#include "stdafx.h"
#include "ZeroFxBloom.h"

ZeroFxBloom::ZeroFxBloom(float time, char* renderpage)
    : ZeroIShader(renderpage), m_fTime(time), m_fBeginTime(time), m_fBlur(0.0f) {
	if (!ZeroRTMgr(renderPage)->Shader())
		ZeroRTMgr(renderPage)->SetShader("Texture/Shader/Bloom.fx");
	else {
		SetErase(true);
		SetRightErase(true);
	}
}
ZeroFxBloom::~ZeroFxBloom() {}

void ZeroFxBloom::Update(float eTime) {
	ZeroIShader::Update(eTime);
	if (IsRightErase()) return;

	m_fTime -= eTime;

	m_fBlur = 3.0f * ZeroMathMgr->Sin(180.0f * (m_fBeginTime - m_fTime) / m_fBeginTime);
	ZeroMathMgr->Clamp(m_fBlur, 0, 1);

	if (ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->Shader()->SetFloat("BaseSaturation", 1 - m_fBlur);
	}

	if (m_fTime <= 0) {
		SetErase(true);
		ZeroRTMgr(renderPage)->ClearShader();
	}
}
