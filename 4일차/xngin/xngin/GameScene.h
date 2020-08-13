#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Animation.h"
#include <list>
class GameScene : public Scene
{
private:
	Animation* player;
	std::list<Sprite*> backgroundList;
	std::list<Sprite*> bridgeList;
	bool firstBackground;
	float scrollSpeed;
	float gravity;
	bool doubleJump, isJump;

public:
	GameScene();
	~GameScene();
	void Render();
	void Update(float dTime);
};

