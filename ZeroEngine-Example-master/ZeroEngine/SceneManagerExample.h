#pragma once
#include "Zero.h"

class SceneManagerExample : public ZeroIScene {
private:
	ZeroFont* m_pFont;
	ZeroSprite* m_pSprite;
public:
	SceneManagerExample();
	~SceneManagerExample();

	void Update(float eTime);
	void Render();
};
