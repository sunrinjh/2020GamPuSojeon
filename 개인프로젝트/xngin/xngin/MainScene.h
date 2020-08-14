#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "GameScene.h"
class MainScene : public Scene
{
public:
	MainScene();
	~MainScene();

	Sprite* background;
	Sprite* startButton;
	Sprite* exitButton;
	Sprite* explainButton;
	Sprite* title;

	void Render();
	void Update(float dTime);
};

