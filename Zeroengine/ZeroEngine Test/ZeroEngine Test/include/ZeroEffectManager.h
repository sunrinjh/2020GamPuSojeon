#pragma once

#include "ZeroIEffect.h"

#define ZeroEffectMgr ZeroEffectManager::Instance()

using namespace std;

class ZeroEffectManager {
private:
	ZeroEffectManager();

	list<ZeroIEffect*> effectList;

public:
	~ZeroEffectManager();

	static ZeroEffectManager* Instance();

	void PushEffect(ZeroIEffect* _effect, ZeroVec _position);
	void PushEffect(ZeroIEffect* _effect);
	void PopEffect(ZeroIEffect* _effect);
	void Clear();

	void Update(float _eTime);
	void RenderPage(int _page);
	void RenderPage();
};
