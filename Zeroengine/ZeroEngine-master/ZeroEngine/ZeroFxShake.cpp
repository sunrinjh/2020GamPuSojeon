#include "stdafx.h"
#include "ZeroFxShake.h"
#include "ZeroMathManager.h"
#include "ZeroRenderTargetManager.h"

ZeroFxShake::ZeroFxShake(float _power_0_0p25, float _time, char* _renderPage)
    : ZeroIShader(_renderPage), strength(_power_0_0p25), time(_time), beginTime(_time) {
	if (!ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->SetShader("Texture/Shader/Shake.fx");
	}
	else {
		SetErase(true);
		SetRightErase(true);
	}
}

ZeroFxShake::~ZeroFxShake() {}

void ZeroFxShake::Update(float _eTime) {
	ZeroIShader::Update(_eTime);
	if (IsRightErase()) return;

	time -= _eTime;

	float angle = ZeroMathMgr->RandFloat(0.0f, 3.14f);
	float timeprop = time / beginTime * strength;

	if (ZeroRTMgr(renderPage)->Shader())
		ZeroRTMgr(renderPage)->Shader()->SetFloat("blurX", timeprop * cos(angle));

	if (ZeroRTMgr(renderPage)->Shader())
		ZeroRTMgr(renderPage)->Shader()->SetFloat("blurY", timeprop * sin(angle));

	if (time <= 0) {
		SetErase(true);
		ZeroRTMgr(renderPage)->ClearShader();
	}
}
