#pragma once
#include "Zero.h"

class RenderTargetExample : public ZeroIScene {
private:
	ZeroSprite* m_pSprite;
public:
	RenderTargetExample();
	~RenderTargetExample();

	void Update(float eTime);
	void Render();
};
