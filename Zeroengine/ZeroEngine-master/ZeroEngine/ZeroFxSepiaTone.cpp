#include "stdafx.h"
#include "ZeroFxSepiaTone.h"

ZeroFxSepiaTone::ZeroFxSepiaTone(float _time, char* _renderPage)
    : ZeroIShader(_renderPage), time(_time), beginTime(_time) {
	if (!ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->SetShader("Texture/Shader/SepiaTone.fx");
	}
	else {
		SetErase(true);
		SetRightErase(true);
	}
}

ZeroFxSepiaTone::~ZeroFxSepiaTone() {}

void ZeroFxSepiaTone::Update(float _eTime) {
	ZeroIShader::Update(_eTime);
	if (IsRightErase()) return;

	time -= _eTime;

	if (time <= 0) {
		SetErase(true);
		ZeroRTMgr(renderPage)->ClearShader();
	}
}
