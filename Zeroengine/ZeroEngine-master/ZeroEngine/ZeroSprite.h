#pragma once

#include "ZeroIScene.h"
#include "ZeroResource.h"

class ZeroSprite : public ZeroIScene, public ZeroResource {
private:
	LPDIRECT3DTEXTURE9 texture;
	string texturePath;
	int renderState;

public:
	ZeroSprite(const char* _path, ...);
	~ZeroSprite();

	void Update(float _eTime);
	void Render();

public:
	int RenderState() const {
		return renderState;
	}
	void SetRenderState(int _renderState) {
		renderState = _renderState;
	}

private:
	void ReloadResource();
};
