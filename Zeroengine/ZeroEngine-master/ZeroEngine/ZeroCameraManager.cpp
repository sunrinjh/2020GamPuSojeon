#include "stdafx.h"
#include "ZeroCameraManager.h"
#include "ZeroApplication.h"

ZeroCameraManager::ZeroCameraManager() {
	SetPos(0, 0);
	SetSpeed(5.0f);
	SetTarget(NULL);
	SetCameraOff();
}

ZeroCameraManager::~ZeroCameraManager() {}

ZeroCameraManager* ZeroCameraManager::Instance() {
	static ZeroCameraManager instance;
	return &instance;
}

void ZeroCameraManager::Update(float _eTime) {
	if (followingTarget) {
		if (moveSpeed > 0) {
			currentPosition.x +=
			    (followingTarget->Pos().x - currentPosition.x - (ZeroApp->GetWindowWidth() / 2.0f) +
			     (followingTarget->Width() * followingTarget->Scale().x) / 2) *
			    _eTime * moveSpeed;
			currentPosition.y += (followingTarget->Pos().y - currentPosition.y -
			                      (ZeroApp->GetWindowHeight() / 2.0f) +
			                      (followingTarget->Height() * followingTarget->Scale().y) / 2) *
			                     _eTime * moveSpeed;
		}
		else {
			currentPosition.x = followingTarget->Pos().x +
			                    (followingTarget->Width() * followingTarget->Scale().x) / 2 -
			                    (ZeroApp->GetWindowWidth() / 2.0f);
			currentPosition.y = followingTarget->Pos().y +
			                    (followingTarget->Width() * followingTarget->Scale().y) / 2 -
			                    (ZeroApp->GetWindowHeight() / 2.0f);
		}
	}

	if (currentPosition.x < 0) currentPosition.x = 0.0f;
	if (currentPosition.y < 0) currentPosition.y = 0.0f;
	if (currentPosition.x > mapWidth - ZeroApp->GetWindowWidth())
		currentPosition.x = static_cast<float>(mapWidth - ZeroApp->GetWindowWidth());
	if (currentPosition.y > mapHeight - ZeroApp->GetWindowHeight())
		currentPosition.y = static_cast<float>(mapHeight - ZeroApp->GetWindowHeight());
}

bool ZeroCameraManager::IsCamera() const {
	return isCameraEnabled;
}

void ZeroCameraManager::SetCameraOn() {
	isCameraEnabled = true;
}

void ZeroCameraManager::SetCameraOff() {
	isCameraEnabled = false;
}

ZeroVec ZeroCameraManager::Pos() const {
	return currentPosition;
}

void ZeroCameraManager::SetPos(ZeroVec pos) {
	currentPosition = pos;
}

void ZeroCameraManager::SetPos(float x, float y) {
	currentPosition.x = x;
	currentPosition.y = y;
}

ZeroIScene* ZeroCameraManager::Target() const {
	return followingTarget;
}

void ZeroCameraManager::SetTarget(ZeroIScene* _target) {
	followingTarget = _target;
}

int ZeroCameraManager::Width() const {
	return mapWidth;
}

void ZeroCameraManager::SetWidth(int _mapWidth) {
	mapWidth = _mapWidth;
}

int ZeroCameraManager::Height() const {
	return mapHeight;
}

void ZeroCameraManager::SetHeight(int _mapHeight) {
	mapHeight = _mapHeight;
}

void ZeroCameraManager::SetScreen(int _mapWidth, int _mapHeight) {
	mapWidth = _mapWidth;
	mapHeight = _mapHeight;
}

float ZeroCameraManager::MoveSpeed() const {
	return moveSpeed;
}

void ZeroCameraManager::SetSpeed(float _moveSpeed) {
	moveSpeed = _moveSpeed;
}
