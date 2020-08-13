#include "stdafx.h"
#include "Sprite.h"
Sprite::Sprite(const char* path) {
	texture = textureManager->LoadTextureFromFile(path);

	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	width = desc.Width;
	height = desc.Height;

	visibleRect.left = 0;
	visibleRect.top = 0;
	visibleRect.right = width;
	visibleRect.bottom = height;

	rect = visibleRect;

	color = D3DCOLOR_ARGB(255, 255, 255, 255);

}
Sprite::~Sprite() {

}
void Sprite::Render() {
	Object::Render();
	pd3dSprite->SetTransform(&mat);
	pd3dSprite->Draw(texture, &visibleRect, NULL, NULL, color);
}
void Sprite::setCenter(int width, int height, Sprite* sprite) {
	rect.left = -width / 2;
	rect.top = -height / 2;
	rect.right = width / 2;
	rect.bottom = height / 2;

}
int Sprite::getHeight() {
	return height;
}
int Sprite::getWidth() {
	return width;
}
D3DCOLOR Sprite::getColor() {
	return color;
}
void Sprite::setColor(D3DCOLOR color) {
	this->color = color;
}



