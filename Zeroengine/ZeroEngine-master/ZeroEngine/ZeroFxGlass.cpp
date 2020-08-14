#include "stdafx.h"
#include "ZeroFxGlass.h"
#include "ZeroTextureManager.h"

ZeroFxGlass::ZeroFxGlass(float time, char* glassTex, char* renderpage)
    : ZeroIShader(renderpage), m_fTime(time), m_fBeginTime(time), m_pTexGlass(NULL) {
	if (!ZeroRTMgr(renderPage)->Shader())
		ZeroRTMgr(renderPage)->SetShader("Texture/Shader/Glass.fx");
	else {
		SetErase(true);
		SetRightErase(true);
	}

	m_pTexGlass = ZeroTexMgr->LoadTextureFromFile(glassTex);
}
ZeroFxGlass::~ZeroFxGlass() {}

void ZeroFxGlass::Update(float eTime) {
	ZeroIShader::Update(eTime);
	if (IsRightErase()) return;

	m_fTime -= eTime;
	if (ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->Shader()->SetTexture("NormalMap", m_pTexGlass);
	}

	if (m_fTime <= 0) {
		SetErase(true);
		ZeroRTMgr(renderPage)->ClearShader();
	}
}
