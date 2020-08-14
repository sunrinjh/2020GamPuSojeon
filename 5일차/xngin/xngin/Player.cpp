#include "stdafx.h"
#include "Player.h"
Player::Player() {
	isJump = false;
	doubleJump = false;
	gravity = 9.81;

	playerAnimation = new Animation(50);
	playerAnimation->AddFrame("Resources/Sprites/player1.png");
	playerAnimation->AddFrame("Resources/Sprites/player2.png");
	AddChild(playerAnimation);

	rect = playerAnimation->getRect();
	playerAnimation->setPos(10,0);
}
Player::~Player() {
}
void Player::Render() {
	Object::Render();
	playerAnimation->Render();
}
void Player::Update(float dTime) {
	gravity += 9.81f;
	setPos(getPosX(), getPosY() + gravity * dTime);
	if (isJump) {
		setPos(getPosX(), getPosY() - 300 * dTime);
		if (doubleJump) {
			setPos(getPosX(), getPosY() - 300 * dTime);
		}
		if (inputManager->GetKeyState(VK_UP) == KEY_DOWN || inputManager->GetKeyState(VK_SPACE) == KEY_DOWN) {
			doubleJump = true;
		}
	}
	if (getPosY() > 370) {
		setPos(getPosX(), 370);
		doubleJump = false;
		isJump = false;
	}
	if (inputManager->GetKeyState(VK_UP) == KEY_DOWN || inputManager->GetKeyState(VK_SPACE) == KEY_DOWN) {
		if (getPosY() == 370) {
			isJump = true;
			gravity = 0;
		}
	}

	playerAnimation->Update(dTime);
}