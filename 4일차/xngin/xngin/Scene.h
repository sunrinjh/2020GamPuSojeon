#pragma once
#include "Object.h"
class Scene
{
private:
	std::list<Object*> objectList;
	std::list<Object*> uiList;
public:
	Scene();
	~Scene();
	void Render();
	void Update(float dTime);

	void AddObject(Object* object);
	void RemoveObject(Object* object);
};