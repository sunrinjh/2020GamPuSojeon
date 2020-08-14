#pragma once

#include "ZeroIScene.h"
#include "ZeroResource.h"

class ZeroFont : public ZeroIScene, public ZeroResource {
private:
	LPD3DXFONT font;
	std::string content;
	char* fontName;
	int fontSize;
	int fontWeight;
	DWORD format;
	ZeroVec fontWrapArea;

	void ReloadResource();

public:
	// ZeroFont의 생성자입니다.
	// * _size : 폰트의 크기를 정합니다.
	// * _string : 보이게 될 내용을 정합니다.
	// * _fontname : 사용할 폰트를 정할 수 있으며 기본값은 '맑은 고딕'입니다.
	// * _filename : 외부 경로에서 폰트를 불러올 수 있습니다.
	ZeroFont(UINT _size, char* _string, char* _fontname = "맑은 고딕", char* _filename = NULL);
	~ZeroFont();

	void Render();
	void Update(float _eTime);

	// ZeroFont의 내용을 변경합니다.
	void SetString(int _content);
	void SetString(const char* _format, ...);
	void SetString(string str);

	// ZeroFont의 굵기를 변경합니다.
	// 100 ~ 900까지 100단위로 설정이 가능하며 기본값은 400입니다.
	void SetWeight(int _weight);

	// ZeroFont의 포맷을 변경합니다.
	// 포맷은 이곳을 참고하세요.
	// https://msdn.microsoft.com/ko-kr/library/microsoft.windowsmobile.directx.direct3d.drawtextformat(v=vs.90).aspx
	void SetFormat(DWORD _format);

	// ZeroFont의 최대 영역을 설정합니다.
	// Format에 DT_WORDBREAK 등을 사용할 때 적용됩니다.
	void SetWrapArea(ZeroVec _area);
	void SetWrapArea(int _width, int _height);

	// ZeroFont의 내용을 반환합니다.
	const char* GetString() const;
	// ZeroFont의 포맷을 반환합니다.
	DWORD GetFormat() const;
	// ZeroFont의 최대 영역을 반환합니다.
	ZeroVec GetWrapArea() const;
};
