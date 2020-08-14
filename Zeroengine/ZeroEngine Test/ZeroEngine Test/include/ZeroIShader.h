#pragma once

#include "ZeroRenderTargetManager.h"

class ZeroIShader : public ZeroIScene {
protected:
	bool control;
	char* renderPage;
	bool rightErase;

public:
	ZeroIShader(char* _renderPage);
	~ZeroIShader();

	void Update(float _eTime);
	void Render();

	int IsControl() const {
		return control;
	}
	void SetControl(bool control) {
		control = control;
	}

	bool IsRightErase() const {
		return rightErase;
	}
	void SetRightErase(bool erase) {
		rightErase = erase;
	}
};
