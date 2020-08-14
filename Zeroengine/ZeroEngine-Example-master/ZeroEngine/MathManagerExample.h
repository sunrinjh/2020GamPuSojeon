#pragma once
#include "Zero.h"

class MathManagerExample : public ZeroIScene {
private:
	ZeroSprite* m_pSprite;
	ZeroFont* m_pFont;

	ZeroRegulator* m_pRandRegulator;
public:
	MathManagerExample();
	~MathManagerExample();

	void Update(float eTime);
	void Render();
};
