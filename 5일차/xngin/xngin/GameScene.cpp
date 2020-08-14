#include "stdafx.h"
#include "GameScene.h"
GameScene::GameScene() {
	firstBackground = false;
	scrollSpeed = 500;
	gravity = 0;
	isJump = false;
	doubleJump = false;


	backgroundList.push_back(new Sprite("Resources/Sprites/Background.png"));
	Sprite* tmpBackground = new Sprite("Resources/Sprites/Background2.png");
	tmpBackground->setPos(SCREEN_WIDTH,0);
	backgroundList.push_back(tmpBackground);

	Sprite* tmpBridge = new Sprite("Resources/Sprites/LoopMap.png");
	tmpBridge->setPos(0, 560);
	bridgeList.push_back(tmpBridge);

	Sprite* tempBridge = new Sprite("Resources/Sprites/LoopMap.png");
	tempBridge->setPos(SCREEN_WIDTH, 560);
	bridgeList.push_back(tempBridge);

	Sprite* tmpCoin = new Sprite("Resources/Sprites/coin-yellow.png");
	tmpCoin->setPos(SCREEN_WIDTH, 400);
	coinList.push_back(tmpCoin);


	Sprite* tmpObstacle = new Sprite("Resources/Sprites/Drop.png");
	tmpObstacle->setPos(SCREEN_WIDTH, 500);
	obstacleList.push_back(tmpObstacle);

	player = new Animation(50);
	player->AddFrame("Resources/Sprites/player1.png");
	player->AddFrame("Resources/Sprites/player2.png");
	player->setPos(50, 100);
	
	
}
GameScene::~GameScene() {

}
void GameScene::Render() {
	for (auto& background : backgroundList) {
		background->Render();
	}
	for (auto& bridge : bridgeList) {
		bridge->Render();
	}
	for (auto& obstacle : obstacleList) {
		obstacle->Render();
	}
	for (auto& coin : coinList) {
		coin->Render();
	}
	player->Render();
}
void GameScene::Update(float dTime) {
	Scene::Update(dTime);
	gravity += 9.8f;
	player->setPos(player->getPosX(), player->getPosY() + gravity * dTime);
	if (isJump) {
		player->setPos(player->getPosX(), player->getPosY() - 400 * dTime);
		if (doubleJump) {
			player->setPos(player->getPosX(), player->getPosY() - 300 * dTime);
		}
		if (inputManager->GetKeyState(VK_UP) == KEY_DOWN || inputManager->GetKeyState(VK_SPACE) == KEY_DOWN) {
			doubleJump = true;
		}
	}
	if (player->getPosY() > 370) {
		player->setPos(player->getPosX(), 370);
		doubleJump = false;
		isJump = false;
	}
	if (inputManager->GetKeyState(VK_UP) == KEY_DOWN || inputManager->GetKeyState(VK_SPACE) == KEY_DOWN) {
		if (player->getPosY() == 370) {
			isJump = true;
			gravity = 0;
		}
	}

	player->Update(dTime);
	int backgroundDiff = scrollSpeed * dTime;
	scrollSpeed +=0.1f;
	for (auto iter = backgroundList.begin(); iter != backgroundList.end(); iter++ ) {
		(*iter)->setPos((*iter)->getPosX() - backgroundDiff, (*iter)->getPosY());
		if ((*iter)->getPosX() < -SCREEN_WIDTH ) { // 여기서 10은 조절해도댐
			SAFE_DELETE(*iter);
			iter = backgroundList.erase(iter);
			if (firstBackground) {
				Sprite* tmpBackground = new Sprite("Resources/Sprites/Background2.png");
				tmpBackground->setPos(SCREEN_WIDTH, 0);
				backgroundList.push_back(tmpBackground);
				firstBackground = false;
			}
			else {
				Sprite* tmpBackground = new Sprite("Resources/Sprites/Background.png");
				tmpBackground->setPos(SCREEN_WIDTH, 0);
				backgroundList.push_back(tmpBackground);
				firstBackground = true;

			}
			if (iter == backgroundList.end()) {
				break;
			}
		}
	}
	for (auto iter = bridgeList.begin(); iter != bridgeList.end(); iter++) {
		(*iter)->setPos((*iter)->getPosX() - backgroundDiff, (*iter)->getPosY());
		if ((*iter)->getPosX() < -SCREEN_WIDTH) { // 여기서 10은 조절해도댐
			SAFE_DELETE(*iter);
			iter = bridgeList.erase(iter);

			Sprite* tempBridge = new Sprite("Resources/Sprites/LoopMap.png");
			tempBridge->setPos(SCREEN_WIDTH, 560);
			bridgeList.push_back(tempBridge);

			if (iter == bridgeList.end()) {
				break;
			}
		}
	}
	for (auto iter = coinList.begin(); iter != coinList.end(); iter++) {
		(*iter)->setPos((*iter)->getPosX() - backgroundDiff, (*iter)->getPosY());
		if (player->IsCollisionRect(*iter)) {

		}
		if ((*iter)->getPosX() < -SCREEN_WIDTH) { // 여기서 10은 조절해도댐
			SAFE_DELETE(*iter);
			iter = coinList.erase(iter);

			Sprite* tmpCoin = new Sprite("Resources/Sprites/coin-yellow.png");
			tmpCoin->setPos(SCREEN_WIDTH, 400);
			coinList.push_back(tmpCoin);
			if (iter == coinList.end()) {
				break;
			}
		}
	}

	for (auto iter = obstacleList.begin(); iter != obstacleList.end(); iter++) {
		(*iter)->setPos((*iter)->getPosX() - backgroundDiff, (*iter)->getPosY());
		if (player->IsCollisionRect(*iter)) {
			sceneManager->ChangeScene(new MainScene());
			return;
		}
		if ((*iter)->getPosX() < -SCREEN_WIDTH) { // 여기서 10은 조절해도댐
			SAFE_DELETE(*iter);
			iter = obstacleList.erase(iter);

			Sprite* tmpObstacle = new Sprite("Resources/Sprites/Drop.png");
			tmpObstacle->setPos(SCREEN_WIDTH, 500);
			obstacleList.push_back(tmpObstacle);
			if (iter == obstacleList.end()) {
				break;
			}
		}
	}
}