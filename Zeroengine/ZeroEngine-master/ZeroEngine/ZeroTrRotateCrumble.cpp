#include "stdafx.h"
#include "ZeroTrRotateCrumble.h"
#include "ZeroTextureManager.h"

ZeroTrRotateCrumble::ZeroTrRotateCrumble(float _time,
                                         char* _renderPage,
                                         LPDIRECT3DTEXTURE9 _secondTexture)
    : ZeroIShader(_renderPage),
      time(_time),
      beginTime(_time),
      secondTexture(_secondTexture),
      m_pCloudTex(NULL) {
	if (!ZeroRTMgr(renderPage)->Shader())
		ZeroRTMgr(renderPage)->SetShader("Texture/Transition/RotateCrumble.fx");
	else
		SetErase(true);

	m_pCloudTex = ZeroTexMgr->LoadTextureFromFile("Texture/Transition/Cloud.png");
}
ZeroTrRotateCrumble::~ZeroTrRotateCrumble() {}

void ZeroTrRotateCrumble::Update(float _eTime) {
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
