#include "stdafx.h"
#include "ZeroRenderTargetManager.h"

ZeroRenderTargetManager::ZeroRenderTargetManager() {}

ZeroRenderTargetManager::~ZeroRenderTargetManager() {
	for (RT::iterator iter = renderTargets.begin(); iter != renderTargets.end(); ++iter) {
		SAFE_DELETE(iter->second);
	}
	renderTargets.clear();
}

ZeroRenderTargetManager* ZeroRenderTargetManager::Instance() {
	static ZeroRenderTargetManager instance;
	return &instance;
}

ZeroRenderTarget* ZeroRenderTargetManager::LoadRenderTarget(char* _page, ...) {
	char buffer[256] = { 0 };
	char* data = buffer;
	va_list vargs;
	va_start(vargs, _page);
	int ret = vsnprintf(data, sizeof(buffer), _page, vargs);
	va_end(vargs);
	if (ret + 1 > sizeof(buffer)) data = static_cast<char*>(malloc(ret + 1));
	va_start(vargs, _page);
	vsprintf(data, _page, vargs);
	va_end(vargs);
	std::string args(data);
	if (data != buffer) free(data);

	if (renderTargets[args] != NULL) {
		return renderTargets[args];
	}

	renderTargets[args] = new ZeroRenderTarget();

	return renderTargets[args];
}

void ZeroRenderTargetManager::ClearAllShaders() {
	for (RT::iterator iter = renderTargets.begin(); iter != renderTargets.end(); ++iter) {
		iter->second->ClearShader();
	}
}
