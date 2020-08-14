#pragma once
#include "Object.h"
#include "Animation.h"
class Player : public Object
{
private: 
	Animation* playerAnimation;
	float gravity;
	bool doubleJump, isJump;
public:
	Player();
	~Player();

	void Render();
	void Update(float dTime);

	
};

