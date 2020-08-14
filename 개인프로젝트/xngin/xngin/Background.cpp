#include "stdafx.h"
#include "Background.h"
Background::Background() {
	background = new Sprite("Resources/Sprites/Background2.png");
	AddChild(background);
	backgroundDiff = 500;
}
Background::~Background() {

}
void Background::Render() {
	Object::Render();
	background->Render();
}
void Background::Update(float dTime) {
	Object::Update(dTime);
}
void Background::setBackgroundDiff(int backgroundDiff) {
	this->backgroundDiff = backgroundDiff;
}