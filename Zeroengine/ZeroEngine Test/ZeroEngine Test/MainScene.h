#pragma once
#include "include/ZeroIScene.h"
class MainScene :
	public ZeroIScene
{
public :
	MainScene();
	~MainScene();

	void Update(float eTime);
	void Render();
};

