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
bool Object::IsCollisionRect(D3DXVECTOR2 p1, D3DXVECTOR2 p2, RECT r1, RECT r2) {
	RECT r;

	r1.left += p1.x;
	r1.right += p1.x;
	r1.top += p1.y;
	r1.bottom += p1.y;

	r2.left += p2.x;
	r2.right += p2.x;
	r2.top += p2.y;
	r2.bottom += p2.y;

	return IntersectRect(&r, &r1, &r2);
}
bool Object::IsPointInRect(D3DXVECTOR2 p, RECT r, D3DXVECTOR2 pt) {
	r.left += p.x;
	r.right += p.x;
	r.top += p.y;
	r.bottom += p.y;

	return (pt.x > r.left && pt.x<r.right && pt.y > r.top && pt.y < r.bottom);
}
D3DXMATRIX Object::getMat() {
	return mat;
}
D3DXVECTOR2 Object::getPos(){
	return pos;
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
