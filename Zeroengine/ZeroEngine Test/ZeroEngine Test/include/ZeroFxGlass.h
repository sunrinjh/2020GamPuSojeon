#pragma once
#include "ZeroIShader.h"

class ZeroFxGlass : public ZeroIShader {
private:
	LPDIRECT3DTEXTURE9 m_pTexGlass;
	float m_fTime;
	float m_fBeginTime;

public:
	ZeroFxGlass(float time, char* glassTex, char* renderpage);
	~ZeroFxGlass();

	void Update(float eTime);
};
