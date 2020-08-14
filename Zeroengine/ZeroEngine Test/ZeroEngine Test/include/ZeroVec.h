#pragma once

#include "ZeroMathManager.h"

// 유용한 상수들
const int MaxInt = (std::numeric_limits<int>::max)();
const double MaxDouble = (std::numeric_limits<double>::max)();
const double MinDouble = (std::numeric_limits<double>::min)();
const float MaxFloat = (std::numeric_limits<float>::max)();
const float MinFloat = (std::numeric_limits<float>::min)();

class ZeroVec : public D3DXVECTOR2 {
public:
	// 기본 생성자입니다.
	ZeroVec() {
		x = 0.0f, y = 0.0f;
	}

	// x, y값으로 벡터를 초기화합니다.
	template <typename T, typename U>
	ZeroVec(T x, U y) {
		this->x = static_cast<float>(x);
		this->y = static_cast<float>(y);
	}

	// f값으로 벡터를 초기화합니다.
	template <typename T>
	ZeroVec(T f) {
		x = static_cast<float>(f);
		y = static_cast<float>(f);
	}

	// (0,0)으로 초기화 합니다.
	void Zero() {
		x = 0.0f;
		y = 0.0f;
	}

	// 벡터가 (0,0)인지 확인합니다.
	bool IsZero() const {
		return (x * x + y * y) < MinDouble;
	}

	// 벡터의 길이를 반환합니다.
	float Length() const;

	// 벡터의 길이 제곱을 반환합니다.
	float LengthSq() const;

	// 벡터를 정규화합니다.
	void Normalize();

	// 벡터의 내적을 반환합니다.
	float Dot(const ZeroVec& vec) const;

	// vec이 현재 벡터의 시계방향에 있으면 양의 값을 반환합니다.
	// 반시계 방향이면 음의 값을 반환합니다.
	int Sign(const ZeroVec& vec) const;

	// 현재 벡터의 수직인 벡터를 반환합니다.
	ZeroVec Perp() const;

	// 벡터 길이가 최대값을 넘지 않도록 x와 y를 조정합니다.
	void Truncate(float max);

	// 현재 벡터와 vec간의 거리를 반환합니다.
	float Distance(const ZeroVec& vec) const;

	// 현재 벡터와 vec간의 거리의 제곱을 반환합니다.
	float DistanceSq(const ZeroVec& vec) const;

	// 주어진 정규화 벡터를 가지고 반사벡터를 만듭니다.
	void Reflect(const ZeroVec& norm);

	// 현재 벡터를 거꾸로 만든 것을 반환합니다.
	ZeroVec GetReverse() const;

	// operator
	ZeroVec& operator+=(CONST ZeroVec&);
	ZeroVec& operator-=(CONST ZeroVec&);
	ZeroVec& operator*=(FLOAT);
	ZeroVec& operator/=(FLOAT);

	// unary operators
	ZeroVec operator+() const;
	ZeroVec operator-() const;

	// binary operators
	ZeroVec operator+(CONST ZeroVec&) const;
	ZeroVec operator-(CONST ZeroVec&) const;
	ZeroVec operator*(FLOAT) const;
	ZeroVec operator/(FLOAT) const;

	friend ZeroVec operator*(FLOAT, CONST ZeroVec&);

	BOOL operator==(CONST ZeroVec&) const;
	BOOL operator!=(CONST ZeroVec&) const;
};

std::ostream& operator<<(std::ostream& os, const ZeroVec& rhs);

// 인라인 함수들

// ------------------------------------------------------------------------non member functions

inline ZeroVec ZeroVecNormalize(const ZeroVec& v) {
	ZeroVec vec = v;

	float vector_length = vec.Length();

	if (vector_length > std::numeric_limits<double>::epsilon()) {
		vec.x /= vector_length;
		vec.y /= vector_length;
	}

	return vec;
}

inline float ZeroVecDistance(const ZeroVec& v1, const ZeroVec& v2) {
	float ySeparation = v2.y - v1.y;
	float xSeparation = v2.x - v1.x;

	return sqrt(ySeparation * ySeparation + xSeparation * xSeparation);
}

inline float ZeroVecDistanceSq(const ZeroVec& v1, const ZeroVec& v2) {
	float ySeparation = v2.y - v1.y;
	float xSeparation = v2.x - v1.x;

	return ySeparation * ySeparation + xSeparation * xSeparation;
}

inline float ZeroVecLength(const ZeroVec& v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

inline float ZeroVecLengthSq(const ZeroVec& v) {
	return (v.x * v.x + v.y * v.y);
}
