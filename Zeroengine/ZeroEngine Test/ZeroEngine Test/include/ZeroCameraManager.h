#pragma once

#include "ZeroIScene.h"

#define ZeroCameraMgr ZeroCameraManager::Instance()

class ZeroCameraManager {
private:
	ZeroVec currentPosition;
	ZeroIScene* followingTarget;

	bool isCameraEnabled;

	// 카메라가 이동 가능한 위치는 (0, 0)부터 (mapWidth, mapHeight) 사이입니다.
	int mapWidth, mapHeight;
	float moveSpeed;

	// 싱글 톤
	ZeroCameraManager();

public:
	~ZeroCameraManager();
	static ZeroCameraManager* Instance();

	void Update(float eTime);

	// 카메라가 활성화되었는지 여부를 반환합니다.
	bool IsCamera() const;
	// 카메라를 활성화합니다.
	void SetCameraOn();
	// 카메라를 비활성화합니다.
	void SetCameraOff();

	// 현재 카메라의 위치를 반환합니다.
	ZeroVec Pos() const;
	// 현재 카메라의 위치를 설정합니다.
	void SetPos(ZeroVec pos);
	// 현재 카메라의 위치를 설정합니다.
	void SetPos(float x, float y);

	// 카메라가 추적하고 있는 대상을 반환합니다.
	ZeroIScene* Target() const;
	// 카메라가 추적할 대상을 설정합니다.
	void SetTarget(ZeroIScene* _target);

	// 맵의 너비를 반환합니다.
	int Width() const;
	// 맵의 너비를 설정합니다.
	void SetWidth(int _mapWidth);

	// 맵의 높이를 반환합니다.
	int Height() const;
	// 맵의 높이를 설정합니다.
	void SetHeight(int _mapHeight);
	// 맵의 크기를 설정합니다.
	void SetScreen(int _mapWidth, int _mapHeight);

	// 카메라의 이동 속도를 반환합니다.
	float MoveSpeed() const;
	// 카메라의 이동 속도를 설정합니다.
	void SetSpeed(float _moveSpeed);
};
