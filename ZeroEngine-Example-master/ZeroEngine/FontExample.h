#pragma once
#include "Zero.h"

class FontExample : public ZeroIScene {
private:
	ZeroFont* m_pFont_1;
	ZeroFont* m_pFont_2;
	ZeroFont* m_pFont_3;
	ZeroFont* m_pFont_4;
public:
	FontExample();
	~FontExample();

	void Update(float eTime);
	void Render();
};
