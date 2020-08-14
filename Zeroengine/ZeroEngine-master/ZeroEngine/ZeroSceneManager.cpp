#include "stdafx.h"
#include "ZeroSceneManager.h"
#include "ZeroRenderTargetManager.h"
#include "ZeroTransition.h"

ZeroSceneManager::ZeroSceneManager()
    : now(NULL), temp(NULL), shader(NULL), m_fChangeTime(2.0f), m_bErase(true) {
	shader = new ZeroIScene();
}

ZeroSceneManager::~ZeroSceneManager() {}

ZeroSceneManager* ZeroSceneManager::Instance() {
	static ZeroSceneManager instance;
	return &instance;
}

void ZeroSceneManager::Update(float _eTime) {
	if (temp) {
		shader->Update(_eTime);
		m_fChangeTime -= _eTime;

		if (m_fChangeTime <= 0) {
			if (m_bErase) {
				SAFE_DELETE(now);
			}
			now = temp;
			temp = NULL;
		}
	}

	if (now) now->Update(_eTime);
}

void ZeroSceneManager::Render() {
	if (temp) {
		ZeroRTMgr("Second_TR")->Begin();
		temp->Render();
		ZeroRTMgr("Second_TR")->End();
	}

	if (now) {
		ZeroRTMgr("First_TR")->Begin();
		now->Render();
		ZeroRTMgr("First_TR")->End();
	}

	ZeroRTMgr("First_TR")->Render();
}

void ZeroSceneManager::Clear() {
	SAFE_DELETE(now);
	SAFE_DELETE(temp);
	SAFE_DELETE(shader);
}

void ZeroSceneManager::ChangeScene(ZeroIScene* _scene,
                                   int _kindTr /*=-1*/,
                                   float _time /*=2.0f*/,
                                   bool _isErase /*=true*/) {
	if (_kindTr == TR::None) {
		if (_isErase) SAFE_DELETE(now);
		now = _scene;
		return;
	}

	if (!temp) {
		temp = _scene;
		m_fChangeTime = _time;
		m_bErase = _isErase;
		switch (_kindTr) {
			case TR::BandedSwirl:
				shader->PushScene(
				    new ZeroTrBandedSwirl(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::CircleReveal:
				shader->PushScene(
				    new ZeroTrCircleReveal(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::CircleStretch:
				shader->PushScene(
				    new ZeroTrCircleStretch(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::CloudReveal:
				shader->PushScene(
				    new ZeroTrCloudReveal(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::Crumble:
				shader->PushScene(
				    new ZeroTrCrumble(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::DropFade:
				shader->PushScene(
				    new ZeroTrDropFade(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::Fade:
				shader->PushScene(
				    new ZeroTrFade(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::Pixelate:
				shader->PushScene(
				    new ZeroTrPixelate(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::RadialBlur:
				shader->PushScene(
				    new ZeroTrRadialBlur(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::RadialWiggle:
				shader->PushScene(
				    new ZeroTrRadialWiggle(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::RandomCircleReveal:
				shader->PushScene(new ZeroTrRandomCircleReveal(_time, "First_TR",
				                                               ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::Ripple:
				shader->PushScene(
				    new ZeroTrRipple(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::RotateCrumble:
				shader->PushScene(
				    new ZeroTrRotateCrumble(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::Saturate:
				shader->PushScene(
				    new ZeroTrSaturate(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::SlideIn:
				shader->PushScene(
				    new ZeroTrSlideIn(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
			case TR::SmoothSwirlGrid:
				shader->PushScene(new ZeroTrSmoothSwirlGrid(_time, "First_TR",
				                                            ZeroRTMgr("Second_TR")->Texture()));
				break;
			default:
				shader->PushScene(
				    new ZeroTrFade(_time, "First_TR", ZeroRTMgr("Second_TR")->Texture()));
				break;
		}
		shader->Update(0);
		temp->UpdateWorldPos();
	}
}
