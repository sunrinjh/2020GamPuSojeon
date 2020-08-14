#pragma once
#include "Object.h"
#include "Sprite.h"
class Background : public Object
{
private:
	Sprite* background;
	int backgroundDiff;
public:
	Background();
	~Background();

	void Update(float dTime);
	void Render();
	void setBackgroundDiff(int backgroundDiff);
};

