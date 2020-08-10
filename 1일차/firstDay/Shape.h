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
		cout << "Shape Draw" << endl; // ���� �Լ�
	}
	virtual void scale() = 0; // ���� ���� �Լ�.
};

