#include "stdafx.h"
#include "ZeroFxEdgeDetect.h"
#include "ZeroApplication.h"

ZeroFxEdgeDetect::ZeroFxEdgeDetect(float _time, char* _renderPage)
    : ZeroIShader(_renderPage), time(_time), beginTime(_time) {
	if (!ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->SetShader("Texture/Shader/EdgeDetect.fx");
	}
	else {
		SetErase(true);
		SetRightErase(true);
	}
}

ZeroFxEdgeDetect::~ZeroFxEdgeDetect() {}

void ZeroFxEdgeDetect::Update(float _eTime) {
	ZeroIShader::Update(_eTime);
	if (IsRightErase()) return;

	time -= _eTime;

	D3DXVECTOR4 pixelOffset = D3DXVECTOR4(1.0f / ZeroApp->GetWindowWidth(),
	                                      1.0f / ZeroApp->GetWindowHeight(), 0.0f, 0.0f);
	if (ZeroRTMgr(renderPage)->Shader())
		ZeroRTMgr(renderPage)->Shader()->SetVector("gPixelOffset", &pixelOffset);

	if (time <= 0) {
		SetErase(true);
		ZeroRTMgr(renderPage)->ClearShader();
	}
}
