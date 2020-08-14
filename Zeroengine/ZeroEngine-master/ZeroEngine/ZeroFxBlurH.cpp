#include "stdafx.h"
#include "ZeroFxBlurH.h"
#include "ZeroMathManager.h"

ZeroFxBlurH::ZeroFxBlurH(float _time, char* _renderPage)
    : ZeroIShader(_renderPage), time(_time), beginTime(_time), blur(0.0f) {
	if (!ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->SetShader("Texture/Shader/BlurH.fx");
	}
	else {
		SetErase(true);
		SetRightErase(true);
	}
}

ZeroFxBlurH::~ZeroFxBlurH() {}

void ZeroFxBlurH::Update(float _eTime) {
	ZeroIShader::Update(_eTime);
	if (IsRightErase()) return;

	time -= _eTime;

	blur = 3.0f * ZeroMathMgr->Sin(180.0f * (beginTime - time) / beginTime);
	ZeroMathMgr->Clamp(blur, 0, 1);

	if (ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->Shader()->SetFloat("progress", blur);
	}

	if (time <= 0) {
		SetErase(true);
		ZeroRTMgr(renderPage)->ClearShader();
	}
}
