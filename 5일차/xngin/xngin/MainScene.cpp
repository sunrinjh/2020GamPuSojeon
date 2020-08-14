#include "stdafx.h"
#include "MainScene.h"
MainScene::MainScene() {
	explainButton = nullptr;
	background = new Sprite("Resources/Sprites/Background.png");
	AddObject(background);
	background->setPos(0, 0);

	title = new Sprite("Resources/Sprites/Title.png");
	AddObject(title);
	title->setPos(275, SCREEN_HEIGHT / 10);

	startButton = new Sprite("Resources/Sprites/start.png");

	AddObject(startButton);
	startButton->setCenter(300, 120, startButton);
	startButton->setPos(SCREEN_WIDTH / 2, 250);

	exitButton = new Sprite("Resources/Sprites/exit.png");
	AddObject(exitButton);
	exitButton->setPos(SCREEN_WIDTH / 2, 500);
}
MainScene::~MainScene() {
	// AddObject로 추가한 오브젝트들은 자동으로 사라짐
	// 만약 AddObject 안쓰면 SAFE_DELETE(background)
}
void MainScene::Render() {
	background->Render();
	title->Render();
	startButton->Render();
	exitButton->Render();
}
void MainScene::Update(float dTime) {
	Scene::Update(dTime);
	if (inputManager->GetKeyState(VK_LBUTTON) == KEY_DOWN) {
		if (exitButton->IsPointInRect(inputManager->GetMousePos())) {
			PostQuitMessage(0);
			return;
		}
		if (startButton->IsPointInRect(inputManager->GetMousePos())) {
			sceneManager->ChangeScene(new GameScene());
			return;
		}
	}
}
