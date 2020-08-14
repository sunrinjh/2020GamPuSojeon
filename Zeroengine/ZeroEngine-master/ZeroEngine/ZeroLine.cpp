#include "stdafx.h"
#include "ZeroLine.h"
#include "ZeroApplication.h"

ZeroLine::ZeroLine() {
	D3DXCreateLine(ZeroApp->GetDevice(), &line);
	D3DXCreateLine(ZeroApp->GetDevice(), &utilLine);

	line->SetAntialias(true);
	line->SetPatternScale(1.0f);
	utilLine->SetAntialias(true);
	utilLine->SetPatternScale(1.0f);

	lineWidth = -1;
	lineHeight = -1;
}

ZeroLine::~ZeroLine() {
	line->Release();
	utilLine->Release();
	pointList.clear();
}

void ZeroLine::ReloadResource() {
	line->Release();
	utilLine->Release();
	D3DXCreateLine(ZeroApp->GetDevice(), &line);
	D3DXCreateLine(ZeroApp->GetDevice(), &utilLine);

	line->SetAntialias(true);
	line->SetPatternScale(1.0f);
	utilLine->SetAntialias(true);
	utilLine->SetPatternScale(1.0f);

	if (lineWidth != -1) SetLineWidth(lineWidth);
	if (lineHeight != -1) SetLinePattern(lineHeight);
}

void ZeroLine::Update(float _eTime) {
	ZeroIScene::Update(_eTime);
}

void ZeroLine::Render() {
	ZeroIScene::Render();

	ZeroVec* pos = new ZeroVec[pointList.size()];
	for (int i = 0; i < (int) pointList.size(); i++) {
		pos[i] = pointList[i];
		D3DXVec2TransformCoord(&pos[i], &pos[i], &m_Mat);
	}
	line->Begin();
	line->Draw(pos, (int) pointList.size(), m_Color);
	line->End();

	delete[] pos;
}

void ZeroLine::SetLineWidth(float _width) {
	line->SetWidth(_width);
	utilLine->SetWidth(_width);
	lineWidth = _width;
}

void ZeroLine::SetLinePattern(DWORD _pattern) {
	line->SetPattern(_pattern);
	utilLine->SetPattern(_pattern);
	lineHeight = _pattern;
}

void ZeroLine::PushFrontPoint(int _num, ...) {
	va_list ap;

	// 가변인수 시작
	va_start(ap, _num);

	for (int i = 0; i < _num; i++) {
		POINTLIST::iterator iter = pointList.begin();
		iter += i;
		ZeroVec pos = va_arg(ap, ZeroVec);
		pointList.insert(iter, pos);
	}

	va_end(ap);
}

void ZeroLine::PushBackPoint(int _num, ...) {
	va_list ap;

	// 가변인수 시작
	va_start(ap, _num);
	for (int i = 0; i < _num; i++) {
		ZeroVec pos = va_arg(ap, ZeroVec);
		pointList.push_back(pos);
	}

	va_end(ap);
}

void ZeroLine::PushFrontPoint(ZeroVec _point) {
	POINTLIST::iterator iter = pointList.begin();
	pointList.insert(iter, _point);
}

void ZeroLine::PushBackPoint(ZeroVec _point) {
	pointList.push_back(_point);
}

void ZeroLine::ClearPoint() {
	pointList.clear();
}

void ZeroLine::PopFrontPoint(int _numberToPop) {
	for (int i = 0; i < _numberToPop; i++) {
		if ((int) pointList.size() == 0) break;
		POINTLIST::iterator iter = pointList.begin();
		pointList.erase(iter, iter + 1);
	}
}

void ZeroLine::PopBackPoint(int _numberToPop) {
	for (int i = 0; i < _numberToPop; i++) {
		if ((int) pointList.size() == 0) break;
		pointList.pop_back();
	}
}

void ZeroLine::DrawRect(ZeroRect _rect) {
	ZeroIScene::Render();

	ZeroVec* pos = new ZeroVec[5];

	pos[0] = ZeroVec(_rect.left, _rect.top);
	pos[1] = ZeroVec(_rect.right, _rect.top);
	pos[2] = ZeroVec(_rect.right, _rect.bottom);
	pos[3] = ZeroVec(_rect.left, _rect.bottom);
	pos[4] = ZeroVec(_rect.left, _rect.top);

	for (int i = 0; i < 5; i++) D3DXVec2TransformCoord(&pos[i], &pos[i], &m_Mat);

	utilLine->Begin();
	utilLine->Draw(pos, 5, m_Color);
	utilLine->End();

	delete[] pos;
}

void ZeroLine::DrawCircle(ZeroVec _center, float _radius) {
	ZeroIScene::Render();

	const float numPoints = 20.0f;
	const float angleDegree = 360.0f / numPoints;
	float theta = 0.0f;

	ZeroVec* pos = new ZeroVec[(int) numPoints + 1];
	for (int i = 0; i <= (int) numPoints; i++) {
		pos[i] = ZeroVec(_center.x, _center.y) +
		         _radius * ZeroVec(ZeroMathMgr->Cos(theta), ZeroMathMgr->Sin(theta));
		theta += angleDegree;

		D3DXVec2TransformCoord(&pos[i], &pos[i], &m_Mat);
	}

	utilLine->Begin();
	utilLine->Draw(pos, (int) (numPoints + 1), m_Color);
	utilLine->End();

	delete[] pos;
}
