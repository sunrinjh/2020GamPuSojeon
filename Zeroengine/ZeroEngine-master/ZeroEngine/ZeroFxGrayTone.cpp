#include "stdafx.h"
#include "ZeroFxGrayTone.h"

ZeroFxGrayTone::ZeroFxGrayTone(float _time, char* _renderPage)
    : ZeroIShader(_renderPage), time(_time), beginTime(_time) {
	if (!ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->SetShader("Texture/Shader/GrayTone.fx");
	}
	else {
		SetErase(true);
		SetRightErase(true);
	}
}

ZeroFxGrayTone::~ZeroFxGrayTone() {}

void ZeroFxGrayTone::Update(float _eTime) {
	ZeroIShader::Update(_eTime);
	if (IsRightErase()) return;

	time -= _eTime;

	if (time <= 0) {
		SetErase(true);
		ZeroRTMgr(renderPage)->ClearShader();
	}
}
