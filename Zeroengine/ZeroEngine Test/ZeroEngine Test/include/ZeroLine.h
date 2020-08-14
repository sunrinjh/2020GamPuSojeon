#pragma once

#include "ZeroIScene.h"
#include "ZeroResource.h"

class ZeroLine : public ZeroIScene, public ZeroResource {
private:
	typedef std::vector<ZeroVec> POINTLIST;
	POINTLIST pointList;

	LPD3DXLINE line;
	LPD3DXLINE utilLine;
	float lineWidth;
	DWORD lineHeight;

public:
	ZeroLine();
	~ZeroLine();

	// 포인트들
	void PushFrontPoint(int _num, ...);
	void PushBackPoint(int _num, ...);
	void PushFrontPoint(ZeroVec _point);
	void PushBackPoint(ZeroVec _point);
	void PopFrontPoint(int _numberToPop);
	void PopBackPoint(int _numberToPop);
	void ClearPoint();

	// 속성
	void SetLineWidth(float _width);
	void SetLinePattern(DWORD _pattern);

	// 유틸리티 기능
	void DrawRect(ZeroRect _rect);
	void DrawCircle(ZeroVec _center, float _radius);

	void Update(float _eTime);
	void Render();

private:
	void ReloadResource();
};
