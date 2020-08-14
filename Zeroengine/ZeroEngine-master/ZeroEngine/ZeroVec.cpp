#include "stdafx.h"
#include "ZeroVec.h"

// 벡터의 길이를 반환합니다.
float ZeroVec::Length() const {
	return sqrt(x * x + y * y);
}

// 벡터의 길이 제곱을 반환합니다.
float ZeroVec::LengthSq() const {
	return (x * x + y * y);
}

// 벡터를 정규화합니다.
void ZeroVec::Normalize() {
	float vector_length = this->Length();

	if (vector_length > std::numeric_limits<float>::epsilon()) {
		this->x /= vector_length;
		this->y /= vector_length;
	}
}

// 벡터의 내적을 반환합니다.
float ZeroVec::Dot(const ZeroVec& vec) const {
	return x * vec.x + y * vec.y;
}

enum { clockwise = 1, anticlockwise = -1 };
// vec이 현재 벡터의 시계방향에 있으면 양의 값을 반환합니다.
// 반시계 방향이면 음의 값을 반환합니다.
int ZeroVec::Sign(const ZeroVec& vec) const {
	if (y * vec.x > x * vec.y) {
		return anticlockwise;
	}
	else {
		return clockwise;
	}
}

// 현재 벡터의 수직인 벡터를 반환합니다.
ZeroVec ZeroVec::Perp() const {
	return ZeroVec(-y, x);
}

// 벡터 길이가 최대값을 넘지 않도록 x와 y를 조정합니다.
void ZeroVec::Truncate(float max) {
	if (this->Length() > max) {
		this->Normalize();
		*this *= max;
	}
}

// 현재 벡터와 vec간의 거리를 반환합니다.
float ZeroVec::Distance(const ZeroVec& vec) const {
	float ySeparation = vec.y - y;
	float xSeparation = vec.x - x;

	return sqrt(ySeparation * ySeparation + xSeparation * xSeparation);
}

// 현재 벡터와 vec간의 거리의 제곱을 반환합니다.
float ZeroVec::DistanceSq(const ZeroVec& vec) const {
	float ySeparation = vec.y - y;
	float xSeparation = vec.x - x;

	return (ySeparation * ySeparation + xSeparation * xSeparation);
}

// 주어진 정규화 벡터를 가지고 반사벡터를 만듭니다.
void ZeroVec::Reflect(const ZeroVec& norm) {
	*this += 2.0f * this->Dot(norm) * norm.GetReverse();
}

// 현재 벡터를 거꾸로 만든 것을 반환합니다.
ZeroVec ZeroVec::GetReverse() const {
	return ZeroVec(-this->x, -this->y);
}

ZeroVec& ZeroVec::operator+=(CONST ZeroVec& rhs) {
	x += rhs.x;
	y += rhs.y;
	return *this;
}
ZeroVec& ZeroVec::operator-=(CONST ZeroVec& rhs) {
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}
ZeroVec& ZeroVec::operator*=(FLOAT rhs) {
	x *= rhs;
	y *= rhs;
	return *this;
}
ZeroVec& ZeroVec::operator/=(FLOAT rhs) {
	x /= rhs;
	y /= rhs;
	return *this;
}

// unary operators
ZeroVec ZeroVec::operator+() const {
	return ZeroVec(x, y);
}
ZeroVec ZeroVec::operator-() const {
	return ZeroVec(-x, -y);
}

// binary operators
ZeroVec ZeroVec::operator+(CONST ZeroVec& rhs) const {
	return ZeroVec(x + rhs.x, y + rhs.y);
}
ZeroVec ZeroVec::operator-(CONST ZeroVec& rhs) const {
	return ZeroVec(x - rhs.x, y - rhs.y);
}
ZeroVec ZeroVec::operator*(FLOAT rhs) const {
	return ZeroVec(x * rhs, y * rhs);
}
ZeroVec ZeroVec::operator/(FLOAT rhs) const {
	return ZeroVec(x / rhs, y / rhs);
}
ZeroVec operator*(FLOAT f, CONST ZeroVec& rhs) {
	return ZeroVec(f * rhs.x, f * rhs.y);
}

BOOL ZeroVec::operator==(CONST ZeroVec& rhs) const {
	return (x == rhs.x && y == rhs.y);
}
BOOL ZeroVec::operator!=(CONST ZeroVec& rhs) const {
	return (x != rhs.x || y != rhs.y);
}

std::ostream& operator<<(std::ostream& os, const ZeroVec& rhs) {
	os << "x : " << rhs.x << ",y : " << rhs.y << std::endl;
	return os;
}
