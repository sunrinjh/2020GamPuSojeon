#include "stdafx.h"
#include "Object.h"
Object::Object() {
	pos = D3DXVECTOR2(0, 0);

	rotationCenter = D3DXVECTOR2(0, 0);
	scalingCenter = D3DXVECTOR2(0, 0);

	rotation = 0;
	scale = D3DXVECTOR2(1, 1);

	D3DXMatrixIdentity(&mat);

	rect.top = 0;
	rect.left = 0;
	rect.right = 0;
	rect.bottom = 0;

	parent = nullptr;
}
Object::~Object() {
	for (auto& child : childList) {
		SAFE_DELETE(child);
	}
}
void Object::Render() {
	D3DXMatrixTransformation2D(&mat, &scalingCenter, 0, &scale, &rotationCenter, rotation, &pos);
	if (parent != nullptr) {
		mat *= parent->mat;
	}
}
void Object::Update(float dTime) {
	for (auto& child : childList) {
		child->Update(dTime);
	}
}
void Object::AddChild(Object* child) {
	childList.push_back(child);
	child->parent = this;
}
void Object::RemoveChild(Object* child) {
	childList.remove(child);
	child->parent = nullptr;
}
bool Object::IsCollisionRect(Object* object) {
	RECT r, r1 = rect, r2 = object->getRect();

	r1.left += pos.x;
	r1.right += pos.x;
	r1.top += pos.y;
	r1.bottom += pos.y;

	r2.left += object->getPosX();
	r2.right += object->getPosX();
	r2.top += object->getPosY();
	r2.bottom += object->getPosY();

	return IntersectRect(&r, &r1, &r2);
}
bool Object::IsPointInRect(D3DXVECTOR2 p) {
	return (p.x > rect.left + pos.x && p.x<rect.right + pos.x && p.y > rect.top + pos.y && p.y < rect.bottom + pos.y);
}
D3DXMATRIX Object::getMat() {
	return mat;
}
D3DXVECTOR2 Object::getPos(){
	return pos;
}
RECT Object::getRect() {
	return rect;
}
int Object::getPosX() {
	return pos.x;
}
int Object::getPosY() {
	return pos.y;
}
void Object::setParent(Object* parent) {
	this->parent = parent;
}
void Object::setPos(int x, int y) {
	pos.x = x;
	pos.y = y;
}
void Object::setPos(D3DXVECTOR2 pos) {
	this->pos = pos;
}
