#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Animation.h"
#include "MainScene.h"
#include <list>
class GameScene : public Scene
{
private:
	Animation* player;
	std::list<Sprite*> backgroundList;
	std::list<Sprite*> bridgeList;
	std::list<Sprite*> obstacleList;
	std::list<Sprite*> coinList;
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

