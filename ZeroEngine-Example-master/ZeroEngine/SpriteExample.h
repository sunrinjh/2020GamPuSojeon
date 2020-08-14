#pragma once
#include "Zero.h"

class SpriteExample : public ZeroIScene {
private:
	//사진 한장
	ZeroSprite* m_pSprite;
public:
	SpriteExample();
	~SpriteExample();

	void Update(float eTime);
	void Render();
};
