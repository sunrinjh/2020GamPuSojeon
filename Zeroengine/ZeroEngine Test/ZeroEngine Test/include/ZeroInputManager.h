#pragma once

#include "ZeroRect.h"
#include "ZeroVec.h"

#define ZeroInputMgr ZeroInputManager::Instance()

enum {
	INPUTMGR_KEYNONE,
	INPUTMGR_KEYON,
	INPUTMGR_KEYDOWN,
	INPUTMGR_KEYUP,

	INPUTMGR_WHEELNONE,
	INPUTMGR_WHEELDOWN,
	INPUTMGR_WHEELUP,
};

class ZeroInputManager {
private:
	ZeroInputManager();

	bool previousKey[256];
	bool currentKey[256];
	bool lockKey[256];

	int wheel;

public:
	~ZeroInputManager();

	static ZeroInputManager* Instance();

	void KeyState();
	int GetKey(int _key);
	void LockKey(int _key);
	void UnlockKey(int _key);

	ZeroVec GetClientPoint();
	ZeroVec GetScreenPoint();
	ZeroRect GetClientRect();
	ZeroRect GetScreenRect();

	int GetWheel();
	void WheelState(WPARAM _wParam);
};
