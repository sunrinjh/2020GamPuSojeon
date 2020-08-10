#pragma once
#include <iostream>
using namespace std;
class Shape
{
protected:
	int x, y;
public:
	void setOrigin(int x, int y) {
		this->x = x;
		this->y = y;
	}
	virtual void draw() {
		cout << "Shape Draw" << endl; // 가상 함수
	}
	virtual void scale() = 0; // 순수 가상 함수.
};

