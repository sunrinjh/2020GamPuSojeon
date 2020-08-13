#include "stdafx.h"
#include "MainScene.h"
MainScene::MainScene() {
	background = new Sprite("Resources/Sprites/Background.png");
	AddObject(background);
	background->setPos(0, 0);
}
MainScene::~MainScene() {
	// AddObject로 추가한 오브젝트들은 자동으로 사라짐
	// 만약 AddObject 안쓰면 SAFE_DELETE(background)
}
void MainScene::Render() {
	background->Render();
}
void MainScene::Update(float dTime) {
	Scene::Update(dTime);
}
