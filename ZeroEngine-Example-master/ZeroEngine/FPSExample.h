#pragma once
#include "Zero.h"

class FPSExample : public ZeroIScene {
private:
	ZeroFont* m_pProcessChecker;
	ZeroRegulator* m_pProcessCheckRegulator;
public:
	FPSExample();
	~FPSExample();

	void Update(float eTime);
	void Render();
};
