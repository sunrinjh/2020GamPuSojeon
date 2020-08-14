#pragma once

#include "ZeroVec.h"

struct ZeroRect : public RECT {
public:
	ZeroRect() {
		Zero();
	}

	ZeroRect(ZeroVec _leftTop, ZeroVec _bottomRight) {
		Set(_leftTop, _bottomRight);
	}

	template <typename T, typename U, typename V, typename W>
	ZeroRect(T _left, U _top, V _right, W _bottom) {
		Set(_left, _top, _right, _bottom);
	}

	void Zero() {
		left = 0L;
		top = 0L;
		bottom = 0L;
		right = 0L;
	}

	void Set(ZeroVec _leftTop, ZeroVec _bottomRight) {
		left = (LONG) _leftTop.x;
		top = (LONG) _leftTop.y;
		right = (LONG) _bottomRight.x;
		bottom = (LONG) _bottomRight.y;
	}

	template <typename T, typename U, typename V, typename W>
	void Set(T _left, U _top, V _right, W _bottom) {
		left = (LONG) _left;
		top = (LONG) _top;
		right = (LONG) _right;
		bottom = (LONG) _bottom;
	}

	void FlipH() {
		left = -left;
		right = -right;
	}

	void FlipV() {
		top = -top;
		bottom = -bottom;
	}

	LONG Width()
	{
		return abs(right - left);
	}

	LONG Height()
	{
		return abs(bottom - top);
	}
};
