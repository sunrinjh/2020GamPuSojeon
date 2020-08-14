#include "stdafx.h"
#include "ZeroTrSaturate.h"

ZeroTrSaturate::ZeroTrSaturate(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture)
    : ZeroIShader(_renderPage), time(_time), beginTime(_time), secondTexture(_secondTexture) {
	if (!ZeroRTMgr(renderPage)->Shader())
		ZeroRTMgr(renderPage)->SetShader("Texture/Transition/Saturate.fx");
	else
		SetErase(true);
}
ZeroTrSaturate::~ZeroTrSaturate() {}

void ZeroTrSaturate::Update(float _eTime) {
	time -= _eTime;

	if (ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->Shader()->SetFloat("Progress", 1.0f - time / beginTime);
		ZeroRTMgr(renderPage)->Shader()->SetTexture("Input2", secondTexture);
	}

	if (time <= 0) {
		SetErase(true);
		ZeroRTMgr(renderPage)->ClearShader();
	}
}
