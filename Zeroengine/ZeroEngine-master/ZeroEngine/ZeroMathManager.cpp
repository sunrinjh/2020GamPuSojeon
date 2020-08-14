#include "stdafx.h"
#include "ZeroMathManager.h"

ZeroMathManager::ZeroMathManager() {
	for (int i = 0; i < 360; ++i) {
		sinTable[i] = sin(DegToRad(static_cast<float>(i)));
		cosTable[i] = cos(DegToRad(static_cast<float>(i)));
	}
}

ZeroMathManager::~ZeroMathManager() {}

ZeroMathManager* ZeroMathManager::Instance() {
	static ZeroMathManager instance;
	return &instance;
}

int ZeroMathManager::RandInt(int _x, int _y) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(_x, _y);
	return dist(mt);
}

float ZeroMathManager::RandFloat(float _x, float _y) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> dist(_x, _y);
	return dist(mt);
}
