#pragma once
#include "Point.h"
class ColorPoint : public Point
{
private:
	string color;
public:
	void setColor(string color) {
		this->color = color;
	}
	void showColorPoint() {
		cout << color << endl;
		showPoint();
	}
};

