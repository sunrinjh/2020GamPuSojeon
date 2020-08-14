#pragma once
#include "Zero.h"

class CameraExample : public ZeroIScene {
private:
	ZeroAnimation* m_pCharacter;
	ZeroSprite* m_pInterface;
	ZeroSprite* m_pTemp;
public:
	CameraExample();
	~CameraExample();

	void Update(float eTime);
	void Render();
};
