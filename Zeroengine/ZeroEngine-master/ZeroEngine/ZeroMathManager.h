#pragma once

#define ZeroMathMgr ZeroMathManager::Instance()

class ZeroMathManager {
private:
	ZeroMathManager();

	float sinTable[360];
	float cosTable[360];

public:
	~ZeroMathManager();

	static ZeroMathManager* Instance();

	template <typename T>
	float DegToRad(T _degree) {
		return static_cast<float>(Pi * (_degree / 180.0f));
	}

	template <typename T>
	float RadToDeg(T _radian) {
		return static_cast<float>(_radian * 180.0f / Pi);
	}

	template <typename T>
	bool InRange(T _start, T _end, T _val) {
		if (_start < _end) {
			if ((_val > _start) && (_val < _end))
				return true;
			else
				return false;
		}
		else {
			if ((_val < _start) && (_val > _end))
				return true;
			else
				return false;
		}
	}

	template <typename T>
	T Max(const T& _v1, const T& _v2) {
		return std::max({ _v1, _v2 });
	}

	template <typename T>
	T Min(const T& _v1, const T& _v2) {
		return std::min({ _v1, _v2 });
	}

	template <typename T, typename U, typename V>
	void Clamp(T& arg, const U& _minVal, const V& _maxVal) {
		if (arg < (T) _minVal) arg = (T) _minVal;
		if (arg > (T) _maxVal) arg = (T) _maxVal;
	}
	// -------------------------- Rand Functions --------------------------//

	int RandInt(int _x, int _y);
	float RandFloat(float _x, float _y);

	// -------------------------- Tri Functions --------------------------//

	template <typename T>
	float Sin(T _sin) {
		while (_sin < 0) _sin += 360;
		return sinTable[static_cast<int>(_sin) % 360];
	}
	template <typename T>
	float Cos(T _cos) {
		while (_cos < 0) _cos += 360;
		return cosTable[static_cast<int>(_cos) % 360];
	}

	// -------------------------- Constants --------------------------//

	const int MaxInt = (std::numeric_limits<int>::max)();
	const double MaxDouble = (std::numeric_limits<double>::max)();
	const double MinDouble = (std::numeric_limits<double>::min)();
	const float MaxFloat = (std::numeric_limits<float>::max)();
	const float MinFloat = (std::numeric_limits<float>::min)();

	const double Pi = 3.14159265358979323846264338327950288L;
};
