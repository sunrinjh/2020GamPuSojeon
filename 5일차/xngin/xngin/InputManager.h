#pragma once
#include <d3dx9.h>
class InputManager
{
private:
	bool beforeKey[256], currentKey[256];
public:
	InputManager();
	~InputManager();

	void UpdateKeyState();
	int GetKeyState(int vk);
	D3DXVECTOR2 GetMousePos();
};

