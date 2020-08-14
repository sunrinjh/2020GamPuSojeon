#include "stdafx.h"
#include "ZeroEffectManager.h"

ZeroEffectManager::ZeroEffectManager() {}

ZeroEffectManager::~ZeroEffectManager() {}

ZeroEffectManager* ZeroEffectManager::Instance() {
	static ZeroEffectManager instance;
	return &instance;
}

void ZeroEffectManager::PushEffect(ZeroIEffect* _effect, ZeroVec _position) {
	effectList.push_back(_effect);
	_effect->SetPos(_position);
	_effect->Update(0);
}

void ZeroEffectManager::PushEffect(ZeroIEffect* _effect) {
	effectList.push_back(_effect);
}

void ZeroEffectManager::PopEffect(ZeroIEffect* _effect) {
	if (effectList.size() != 0) effectList.remove(_effect);
}

void ZeroEffectManager::Clear() {
	for (auto iter = effectList.begin(); iter != effectList.end(); ++iter) {
		(*iter)->SetErase(true);
	}
	effectList.clear();
}

void ZeroEffectManager::Update(float _eTime) {
	for (auto iter = effectList.begin(); iter != effectList.end(); ++iter) {
		if ((*iter)->IsErase()) {
			iter = effectList.erase(iter);
			if (iter == effectList.end()) break;
		}
	}
}

void ZeroEffectManager::RenderPage(int _page) {
	for (auto iter = effectList.begin(); iter != effectList.end(); ++iter) {
		if ((*iter)->RenderPage() == _page) (*iter)->Render();
	}
}

void ZeroEffectManager::RenderPage() {
	for (auto iter = effectList.begin(); iter != effectList.end(); ++iter) {
		(*iter)->Render();
	}
}
