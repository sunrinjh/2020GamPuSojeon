#include "stdafx.h"
#include "ZeroInputManager.h"
#include "ZeroApplication.h"
#include "ZeroRect.h"

ZeroInputManager::ZeroInputManager() {
	for (int i = 0; i < 256; i++) {
		previousKey[i] = false;
		currentKey[i] = false;
		lockKey[i] = false;
	}

	wheel = INPUTMGR_WHEELNONE;
}

ZeroInputManager::~ZeroInputManager() {}

ZeroInputManager* ZeroInputManager::Instance() {
	static ZeroInputManager instance;
	return &instance;
}

void ZeroInputManager::KeyState() {
	for (int i = 0; i < 256; i++) {
		previousKey[i] = currentKey[i];
		if (GetKeyState(i) & 0x80) {
			currentKey[i] = true;
		}
		else {
			currentKey[i] = false;
		}
	}
}
int ZeroInputManager::GetKey(int _key) {
	// 게임 창이 최상위가 아닐 경우 모든 키 무시
	if (GetFocus() != ZeroApp->GetHwnd()) return INPUTMGR_KEYNONE;

	if (lockKey[_key]) return INPUTMGR_KEYNONE;

	if (previousKey[_key] && currentKey[_key]) return INPUTMGR_KEYON;

	if (!previousKey[_key] && currentKey[_key]) return INPUTMGR_KEYDOWN;

	if (previousKey[_key] && !currentKey[_key]) return INPUTMGR_KEYUP;

	return INPUTMGR_KEYNONE;
}

void ZeroInputManager::LockKey(int _key) {
	lockKey[_key] = true;
}

void ZeroInputManager::UnlockKey(int _key) {
	lockKey[_key] = false;
}

ZeroVec ZeroInputManager::GetClientPoint() {
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(ZeroApp->GetHwnd(), &pt);
	return ZeroVec(static_cast<float>(pt.x), static_cast<float>(pt.y));
}

ZeroVec ZeroInputManager::GetScreenPoint() {
	POINT pt;
	GetCursorPos(&pt);
	return ZeroVec(static_cast<float>(pt.x), static_cast<float>(pt.y));
}

ZeroRect ZeroInputManager::GetClientRect() {
	int x = static_cast<int>(GetClientPoint().x);
	int y = static_cast<int>(GetClientPoint().y);
	ZeroRect rect(x, y, x + 1, y + 1);
	return rect;
}

ZeroRect ZeroInputManager::GetScreenRect() {
	int x = static_cast<int>(GetScreenPoint().x);
	int y = static_cast<int>(GetScreenPoint().y);
	ZeroRect rect(x, y, x + 1, y + 1);
	return rect;
}

int ZeroInputManager::GetWheel() {
	return wheel;
}

void ZeroInputManager::WheelState(WPARAM _wParam) {
	wheel = static_cast<int>(GET_WHEEL_DELTA_WPARAM(_wParam) / 120.f);
}
