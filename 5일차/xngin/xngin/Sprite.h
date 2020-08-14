#pragma once
#include "Object.h"
class Sprite :
	public Object
{
private:
	LPDIRECT3DTEXTURE9 texture;
	D3DCOLOR color;
	RECT visibleRect;

	int width;
	int height;

public:
	Sprite(const char* path);
	~Sprite();
	void Render();
	int getWidth();
	int getHeight();
	D3DCOLOR getColor();
	void setColor(D3DCOLOR color);
	void setCenter(int width, int height, Sprite* sprite);
};

