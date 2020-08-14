#pragma once
#include "Zero.h"

class SoundExample : public ZeroIScene {
private:
	ZeroFont* status;
public:
	SoundExample();
	~SoundExample();

	void Update(float eTime);
	void Render();
};
