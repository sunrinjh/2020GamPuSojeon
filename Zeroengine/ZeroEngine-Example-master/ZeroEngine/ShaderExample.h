#pragma once
#include "Zero.h"

class ShaderExample : public ZeroIScene {
private:
public:
	ShaderExample();
	~ShaderExample();

	void Update(float eTime);
	void Render();
};
