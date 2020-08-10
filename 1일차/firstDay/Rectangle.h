#pragma once
#include "Shape.h"
class Rectangle :
	public Shape
{
private:
	int width, height;
public:
	void setWidth(int w) {
		width = w;
	}
	void setHeight(int h) {
		height = h;
	}
	void draw(int w) {
		cout << "Rectangle Draw" << endl;
	}
};

