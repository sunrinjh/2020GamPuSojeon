#pragma once
#include "Zero.h"

class InputManagerExample : public ZeroIScene {
private:
	ZeroSprite* m_pSprite;
	ZeroSprite* m_pTemp;
public:
	InputManagerExample();
	~InputManagerExample();

	void Update(float eTime);
	void Render();
};
