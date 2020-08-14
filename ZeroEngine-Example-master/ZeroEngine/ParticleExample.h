#pragma once
#include "Zero.h"

class ParticleExample : public ZeroIScene {
private:
public:
	ParticleExample();
	~ParticleExample();

	void Update(float eTime);
	void Render();
};
