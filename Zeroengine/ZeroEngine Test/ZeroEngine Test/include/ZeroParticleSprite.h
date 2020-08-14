#pragma once

#include "ZeroIEffect.h"
#include "ZeroIParticle.h"

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

class ZeroParticleSprite : public ZeroIEffect {
private:
	typedef std::vector<ZeroIParticle*> PARTICLE;
	PARTICLE particleList;

	int startA, startR, startG, startB;
	int endA, endR, endG, endB;

	char* path;
	int count;
	int size;
	int renderState;
	float time;

	float minSpeed, maxSpeed;
	float minScale, maxScale;
	float minLifeTime, maxLifeTime;
	float rotSpeed;
	float direction;
	float spread;

	void PushParticle(ZeroIParticle* p);
	void CreateParticle();

public:
	ZeroParticleSprite(const char* _path, int _size = 1);
	~ZeroParticleSprite();

	void Start();

	void Update(float _eTime);
	void Render();

	void SetParticleColorStart(int _a, int _r, int _g, int _b) {
		startA = _a, startR = _r, startG = _g, startB = _b;
	}

	void SetParticleColorEnd(int _a, int _r, int _g, int _b) {
		endA = _a, endR = _r, endG = _g, endB = _b;
	}

	template <typename T, typename U>
	void SetParticleSpeed(T _minSpeed, U _maxSpeed) {
		minSpeed = static_cast<float>(_minSpeed);
		maxSpeed = static_cast<float>(_maxSpeed);
	}

	template <typename T, typename U>
	void SetParticleScale(T _minScale, U _maxScale) {
		minScale = static_cast<float>(_minScale);
		maxScale = static_cast<float>(_maxScale);
	}

	template <typename T, typename U>
	void SetParticleLifeTime(T _minLifeTime, U _maxLifeTime) {
		minLifeTime = static_cast<float>(_minLifeTime);
		maxLifeTime = static_cast<float>(_maxLifeTime);
	}

	template <typename T>
	void SetParticleDirection(T _direction) {
		direction = static_cast<float>(_direction);
	}

	template <typename T>
	void SetParticleSpread(T _spread) {
		spread = static_cast<float>(_spread);
	}

	void SetRenderState(int _renderState) {
		renderState = _renderState;
	}
};
