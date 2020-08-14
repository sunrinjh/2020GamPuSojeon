#pragma once

#include "ZeroIScene.h"
#include "ZeroMat.h"
#include "ZeroResource.h"

class ZeroRenderTarget : public ZeroResource {
public:
	enum {
		BLENDING_NORMAL,
		BLENDING_LIGHTEN,
		BLENDING_DARKEN,
		BLENDING_MOREDARKEN,
	};

private:
	LPDIRECT3DTEXTURE9 texture;
	LPDIRECT3DSURFACE9 surface;
	LPDIRECT3DSURFACE9 original;
	LPD3DXEFFECT shader;
	string shaderPath;
	bool isBegin;

	ZeroRect rect;

	int width, height;

public:
	ZeroRenderTarget();
	~ZeroRenderTarget();

	void SetShader(const char* _path);
	void ClearShader();

	LPD3DXEFFECT Shader() const {
		return shader;
	}

	LPDIRECT3DTEXTURE9 Texture() const {
		return texture;
	}

	void Render(D3DXMATRIX* _mat = NULL);
	void Update(float _eTime);
	void Begin(bool _clear = true);
	void End();

	// 본 객체의 테두리값을 반환한다.
	ZeroRect Rect() const {
		return rect;
	}

	// 본 객체의 테두리 값을 설정한다.
	void SetRect(ZeroRect _rect) {
		rect = _rect;
	}

	template <typename T, typename U, typename V, typename W>
	// 본 객체의 테두리값을 left, top, right, bottom 순으로 설정한다.
	void SetRect(T _left, U _top, V _right, W _bottom) {
		rect.left = static_cast<LONG>(_left);
		rect.top = static_cast<LONG>(_top);
		rect.right = static_cast<LONG>(_right);
		rect.bottom = static_cast<LONG>(_bottom);
	}

	int Width() const {
		return width;
	}
	int Height() const {
		return height;
	}
	void SetWidth(int width);
	void SetHeight(int height);
	void SetSize(int width, int height);

private:
	void OnPrevDeviceReset();
	void OnPostDeviceReset();
};
