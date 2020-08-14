#include "stdafx.h"
#include "ZeroFxRadialBlur.h"
#include "ZeroMathManager.h"

ZeroFxRadialBlur::ZeroFxRadialBlur(float _time, float _power_0_1, char* _renderPage)
    : ZeroIShader(_renderPage),
      time(_time),
      beginTime(_time),
      center(0.5f, 0.5f, 0.f, 0.f),
      blurStart(1.0f),
      blurWidth(0.0f),
      power(_power_0_1) {
	if (!ZeroRTMgr(renderPage)->Shader())
		ZeroRTMgr(renderPage)->SetShader("Texture/Shader/RadialBlur.fx");
	else {
		SetErase(true);
		SetRightErase(true);
	}
}

ZeroFxRadialBlur::~ZeroFxRadialBlur() {}

void ZeroFxRadialBlur::Update(float _eTime) {
	ZeroIShader::Update(_eTime);
	if (IsRightErase()) {
		return;
	}

	time -= _eTime;
	blurWidth = power * 3.0f * ZeroMathMgr->Sin(180.0f * (beginTime - time) / beginTime);

	if (power >= 0) {
		ZeroMathMgr->Clamp(blurWidth, -power, power);
	}
	else {
		ZeroMathMgr->Clamp(blurWidth, power, -power);
	}

	if (ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->Shader()->SetVector("Center", &center);
		ZeroRTMgr(renderPage)->Shader()->SetFloat("BlurStart", blurStart);
		ZeroRTMgr(renderPage)->Shader()->SetFloat("BlurWidth", blurWidth);
	}

	if (time <= 0) {
		SetErase(true);
		ZeroRTMgr(renderPage)->ClearShader();
	}
}
