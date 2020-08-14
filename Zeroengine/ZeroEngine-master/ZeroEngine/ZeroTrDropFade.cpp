#include "stdafx.h"
#include "ZeroTrDropFade.h"
#include "ZeroTextureManager.h"

ZeroTrDropFade::ZeroTrDropFade(float _time, char* _renderPage, LPDIRECT3DTEXTURE9 _secondTexture)
    : ZeroIShader(_renderPage),
      time(_time),
      beginTime(_time),
      secondTexture(_secondTexture),
      m_pCloudTex(NULL) {
	if (!ZeroRTMgr(renderPage)->Shader())
		ZeroRTMgr(renderPage)->SetShader("Texture/Transition/DropFade.fx");
	else
		SetErase(true);

	m_pCloudTex = ZeroTexMgr->LoadTextureFromFile("Texture/Transition/Cloud.png");
}
ZeroTrDropFade::~ZeroTrDropFade() {}

void ZeroTrDropFade::Update(float _eTime) {
	time -= _eTime;

	if (ZeroRTMgr(renderPage)->Shader()) {
		ZeroRTMgr(renderPage)->Shader()->SetFloat("Progress", 1.0f - time / beginTime);
		ZeroRTMgr(renderPage)->Shader()->SetTexture("Input2", secondTexture);
		ZeroRTMgr(renderPage)->Shader()->SetTexture("InputCloud", m_pCloudTex);
	}

	if (time <= 0) {
		SetErase(true);
		ZeroRTMgr(renderPage)->ClearShader();
	}
}
