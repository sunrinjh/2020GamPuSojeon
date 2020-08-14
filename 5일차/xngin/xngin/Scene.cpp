#include "stdafx.h"
#include "Scene.h"
Scene::Scene() {

}
Scene::~Scene() {
	for (auto& object : objectList) {
		SAFE_DELETE(object);
	}
	for (auto& ui : uiList) {
		SAFE_DELETE(ui);
	}
}
void Scene::Render() {

}
void Scene::Update(float dTime) {
	for (auto& object : objectList) {
		object->Update(dTime);
	}
	for (auto& ui : uiList) {
		ui->Update(dTime);
	}
}
void Scene::AddObject(Object* object) {
	objectList.push_back(object);
	object->setParent(nullptr);
}
void Scene::RemoveObject(Object* object) {
	objectList.remove(object);
}