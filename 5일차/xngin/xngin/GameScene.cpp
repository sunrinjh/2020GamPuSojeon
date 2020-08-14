#include "stdafx.h"
#include "GameScene.h"
GameScene::GameScene() {
	backgroundInstantiate = false;
	scrollSpeed = 500;
	score = 0;

	Background* background = new Background();
	background->setPos(0,0);
	backgroundList.push_back(background);
	AddObject(background);

	Background* tbackground = new Background();
	tbackground->setPos(0, 0);
	backgroundList.push_back(tbackground);
	AddObject(tbackground);

	Sprite* tmpBridge = new Sprite("Resources/Sprites/LoopMap.png");
	tmpBridge->setPos(0, 560);
	bridgeList.push_back(tmpBridge);

	Sprite* tempBridge = new Sprite("Resources/Sprites/LoopMap.png");
	tempBridge->setPos(SCREEN_WIDTH, 560);
	bridgeList.push_back(tempBridge);

	Sprite* tmpCoin = new Sprite("Resources/Sprites/coin-yellow.png");
	tmpCoin->setPos(SCREEN_WIDTH + 70, 400);
	coinList.push_back(tmpCoin);


	Sprite* tmpObstacle = new Sprite("Resources/Sprites/obstacle01.jpg");
	tmpObstacle->setPos(SCREEN_WIDTH, 500);
	obstacleList.push_back(tmpObstacle);
	
	for (int i = 0; i < 4; i++) {
		numArray[i].setPos(0 + 60 * i, 10);
	}
	player = new Player();
	player->setPos(100, 100);
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
	for (int i = 0; i < 4; i++) {
		numArray[i].Render();
	}
	player->Render();
}
void GameScene::Update(float dTime) {
	player->Update(dTime);
	
	Scene::Update(dTime);
	int randNum = rand() % 10 + 1;

	if ((rand() % 10 + 1) == 1) {
		Sprite* tmpCoin = new Sprite("Resources/Sprites/coin-yellow.png");
		tmpCoin->setPos(SCREEN_WIDTH + 100, 400);
		coinList.push_back(tmpCoin);
	}
	numArray[0].setNum(score / 1000);
	numArray[1].setNum(score / 100 % 10);
	numArray[2].setNum(score / 10 % 10 );
	numArray[3].setNum(score % 10);

	int backgroundDiff = scrollSpeed * dTime;
	scrollSpeed +=0.1f;

	for (auto iter = backgroundList.begin(); iter != backgroundList.end(); iter++) {
		(*iter)->setPos((*iter)->getPosX() - backgroundDiff, (*iter)->getPosY());
		if ((*iter)->getPosX() < -SCREEN_WIDTH) { // 여기서 10은 조절해도댐
			RemoveObject((*iter));
			SAFE_DELETE(*iter);
			iter = backgroundList.erase(iter);
			backgroundInstantiate = false;
			if (iter == backgroundList.end()) {
				break;
			}
		}
	}	
	if (!backgroundInstantiate) {
		Background* background = new Background();
		background->setPos(SCREEN_WIDTH, 0);
		backgroundList.push_back(background);
		AddObject(background);
		backgroundInstantiate = true;
		background->setBackgroundDiff(backgroundDiff);
	}
	for (auto iter = bridgeList.begin(); iter != bridgeList.end(); iter++) {
		(*iter)->setPos((*iter)->getPosX() - backgroundDiff, (*iter)->getPosY());
		if ((*iter)->getPosX() < -SCREEN_WIDTH) { // 여기서 10은 조절해도댐
			SAFE_DELETE(*iter);
			iter = bridgeList.erase(iter);

			Sprite* tempBridge = new Sprite("Resources/Sprites/LoopMap.png");
			tempBridge->setPos(SCREEN_WIDTH, 560);
			bridgeList.push_back(tempBridge);
			backgroundInstantiate = false;
			if (iter == bridgeList.end()) {
				break;
			}
		}
	}
	for (auto iter = coinList.begin(); iter != coinList.end(); iter++) {
		(*iter)->setPos((*iter)->getPosX() - backgroundDiff, (*iter)->getPosY());
		if ((*iter)->getPosX() < -SCREEN_WIDTH) { // 여기서 10은 조절해도댐
			SAFE_DELETE(*iter);
			iter = coinList.erase(iter);
			if (iter == coinList.end()) {
				break;
			}
		}
	}
	for (auto iter = coinList.begin(); iter != coinList.end(); iter++) {
		if (player->IsCollisionRect(*iter)) {
			score++;
			SAFE_DELETE(*iter);
			iter = coinList.erase(iter);
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
			int randomSprite = rand() % 17 + 1;
			Sprite* tmpObstacle;
			switch (randomSprite)
			{
				
			case 1:
				 tmpObstacle = new Sprite("Resources/Sprites/obstacle01.jpg");
				 break;
			case 2:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle02.jpg");
				break;
			case 3:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle03.jpg");
				break;
			case 4:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle04.jpg");
				break;
			case 5:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle05.jpg");
				break;
			case 6:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle06.jpg");
				break;
			case 7:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle07.jpg");
				break;
			case 8:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle08.jpg");
				break;
			case 9:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle09.jpg");
				break;
			case 10:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle10.jpg");
				break;
			case 11:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle11.jpg");
				break;
			case 12:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle12.jpg");
				break;
			case 13:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle13.jpg");
				break;
			case 14:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle14.jpg");
				break;
			case 15:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle15.jpg");
				break;
			case 16:
				tmpObstacle = new Sprite("Resources/Sprites/obstacle16.jpg");
				break;

			}
			tmpObstacle->setPos(SCREEN_WIDTH, 500);
			obstacleList.push_back(tmpObstacle);
			
			
			if (iter == obstacleList.end()) {
				break;
			}
		}
	}
}