#include "stdafx.h"
#include "ZeroIShader.h"
#include "ZeroRenderTargetManager.h"

ZeroIShader::ZeroIShader(char* _renderPage)
    : control(false), renderPage(_renderPage), rightErase(false) {}

ZeroIShader::~ZeroIShader() {
	SetErase(true);
	if (!rightErase) {
		ZeroRTMgr(renderPage)->ClearShader();
	}
}

void ZeroIShader::Update(float _eTime) {
	ZeroIScene::Update(_eTime);
}

void ZeroIShader::Render() {
	ZeroIScene::Render();
}
