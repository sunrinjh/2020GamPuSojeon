#pragma once

#include "ZeroRenderTarget.h"

#define SAFE_DELETE(p)  \
	{                   \
		if (p) {        \
			delete (p); \
			(p) = 0;    \
		}               \
	}
#define SAFE_DELETE_ARRAY(p) \
	{                        \
		if (p) {             \
			delete[](p);     \
			(p) = 0;         \
		}                    \
	}
#define SAFE_RELEASE(p)     \
	{                       \
		if (p) {            \
			(p)->Release(); \
			(p) = 0;        \
		}                   \
	}

#define ZeroRTMgr ZeroRenderTargetManager::Instance()->LoadRenderTarget

using namespace std;

class ZeroRenderTargetManager {
private:
	typedef map<string, ZeroRenderTarget*> RT;
	RT renderTargets;
	ZeroRenderTargetManager();

public:
	~ZeroRenderTargetManager();
	static ZeroRenderTargetManager* Instance();
	ZeroRenderTarget* LoadRenderTarget(char* _page, ...);
	void ClearAllShaders();
};
