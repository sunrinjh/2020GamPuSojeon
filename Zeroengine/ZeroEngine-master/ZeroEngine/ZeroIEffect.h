#pragma once

#include "ZeroRenderTargetManager.h"

class ZeroIEffect : public ZeroIScene {
private:
	int renderPage;

public:
	ZeroIEffect();
	~ZeroIEffect();

	void Update(float _eTime);
	void Render();

	int RenderPage() const;
	void SetRenderPage(int _renderPage) {
		renderPage = _renderPage;
	}
};
