#pragma once
#include "Zero.h"

class LineExample : public ZeroIScene {
private:
	ZeroLine* m_pLine;

	ZeroLine* m_pCircle;
public:
	LineExample();
	~LineExample();

	void Update(float eTime);
	void Render();
};
