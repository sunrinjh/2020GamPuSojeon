#include "stdafx.h"
#include "MainScene.h"
MainScene::MainScene() {
	background = new Sprite("Resources/Sprites/Background.png");
	AddObject(background);
	background->setPos(0, 0);
}
MainScene::~MainScene() {
	// AddObject�� �߰��� ������Ʈ���� �ڵ����� �����
	// ���� AddObject �Ⱦ��� SAFE_DELETE(background)
}
void MainScene::Render() {
	background->Render();
}
void MainScene::Update(float dTime) {
	Scene::Update(dTime);
}
