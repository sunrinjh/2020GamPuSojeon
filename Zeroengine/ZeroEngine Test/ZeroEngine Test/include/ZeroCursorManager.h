#pragma once

#include "ZeroResource.h"

#define ZeroCursorMgr ZeroCursorManager::Instance()

class ZeroCursorManager : public ZeroResource {
private:
	ZeroCursorManager();

	LPDIRECT3DSURFACE9 cursorSurface;
	bool isCurserEnabled;

public:
	~ZeroCursorManager();

	void SetCursorShape();
	void UpdateCursorShape();
	void SetCursorOn();
	void SetCursorOff();
	void SetCursorToggle();
	bool IsShowingCursor();

	static ZeroCursorManager* Instance();

private:
	void ReloadResource();
};
