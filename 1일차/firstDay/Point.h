#pragma once
#include <iostream>
#include <string>
using namespace std;
class Point
{
private:
	int x;
	int y;
public:
	void setPoint(int x, int y) {
		this->x = x;
		this->y = y;
	}
	void showPoint() {
		cout << "(" << x << "," << y << ")" << endl;
	}
};

