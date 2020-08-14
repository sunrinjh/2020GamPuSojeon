#pragma once

#include "ZeroIScene.h"
#include "ZeroResource.h"

class ZeroIParticle : public ZeroIScene, public ZeroResource {
private:
	LPDIRECT3DTEXTURE9 texture;
	string texturePath;

	ZeroVec speed;
	float lifeTime;
	float nowLifeTime;
	float rotationSpeed;
	int renderState;

	int colorA, colorR, colorG, colorB;

	void ReloadResource();

public:
	ZeroIParticle(char* _path,
	              ZeroVec _speed,
	              float _lifeTime,
	              float _size,
	              float _rotationSpeed,
	              int _colorA,
	              int _colorR,
	              int _colorG,
	              int _colorB,
	              int _renderState);
	~ZeroIParticle();

	void Render();
	void Update(float _eTime);

	ZeroVec Speed() const {
		return speed;
	}
	float LifeTime() const {
		return lifeTime;
	}
	float NowLifeTime() const {
		return nowLifeTime;
	}
	float RotSpeed() const {
		return rotationSpeed;
	}

	int RenderState() const {
		return renderState;
	}
	void SetRenderState(int _renderState) {
		renderState = _renderState;
	}

	void SetColorA(int a) {
		colorA = a;
	}
	void SetColorR(int r) {
		colorR = r;
	}
	void SetColorG(int g) {
		colorG = g;
	}
	void SetColorB(int b) {
		colorB = b;
	}
};
