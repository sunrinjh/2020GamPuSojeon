#include "stdafx.h"
#include "InputManager.h"

InputManager::InputManager() {
	for (int i = 0; i < 256; i++) {
		beforeKey[i] = false;
		currentKey[i] = false;
	}
}
InputManager::~InputManager() {

}
void InputManager::UpdateKeyState() {
	for (int i = 0; i < 256; i++) {
		beforeKey[i] = currentKey[i];
		currentKey[i] = GetAsyncKeyState(i) & 0x8000;
	}
}
int InputManager::GetKeyState(int vk) { // 현재 키 상태 반환
	if (beforeKey[vk] && currentKey[vk]) {
		return KEY_ON;
	}
	else if (!beforeKey[vk] && currentKey[vk]) {
		return KEY_DOWN;
	}
	else if (beforeKey[vk] && !currentKey[vk]) {
		return KEY_UP;
	}
	else {
		return KEY_NONE;
	}
}
D3DXVECTOR2 InputManager::GetMousePos() { // 마우스 포지션 반환
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hWnd, &p);

	return D3DXVECTOR2(p.x, p.y);
}