#include "stdafx.h"
#include "ZeroTrRipple.h"

ZeroTrRipple::ZeroTrRipple(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture)
    : ZeroIShader(_renderPage), time(_time), beginTime(_time), secondTexture(_secondTexture) {
	if (!ZeroRTMgr(renderPage)->Shader())
		ZeroRTMgr(renderPage)->SetShader("Texture/Transition/Ripple.fx");
	else
		SetErase(true);
}
ZeroTrRipple::~ZeroTrRipple() {}

void ZeroTrRipple::Update(float _eTime) {
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
