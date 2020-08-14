#include "stdafx.h"
#include "ZeroFxNightVision.h"
#include "ZeroTextureManager.h"

ZeroFxNightVision::ZeroFxNightVision(float _time, char* _renderPage)
    : ZeroIShader(_renderPage), time(_time), beginTime(_time), elapsedTime(0.0f), texNoise(NULL) {
	if (!ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->SetShader("Texture/Shader/NightVision.fx");
	}
	else {
		SetErase(true);
		SetRightErase(true);
	}

	texNoise = ZeroTexMgr->LoadTextureFromFile("Texture/Shader/NightVision/Noise.jpg");
}

ZeroFxNightVision::~ZeroFxNightVision() {}

void ZeroFxNightVision::ReloadResource() {
	texNoise = ZeroTexMgr->LoadTextureFromFile("Texture/Shader/NightVision/Noise.jpg");
}

void ZeroFxNightVision::Update(float _eTime) {
	ZeroIShader::Update(_eTime);
	if (IsRightErase()) return;

	time -= _eTime;
	elapsedTime += _eTime;
	if (ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->Shader()->SetFloat("elapsedTime", elapsedTime);
		ZeroRTMgr(renderPage)->Shader()->SetTexture("tex", texNoise);
	}

	if (time <= 0) {
		SetErase(true);
		ZeroRTMgr(renderPage)->ClearShader();
	}
}
