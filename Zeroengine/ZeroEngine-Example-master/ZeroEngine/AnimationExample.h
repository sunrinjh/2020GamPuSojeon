#pragma once
#include "Zero.h"

class AnimationExample : public ZeroIScene {
private:
	ZeroAnimation* m_pAni;
public:
	AnimationExample();
	~AnimationExample();

	void Update(float eTime);
	void Render();
};
