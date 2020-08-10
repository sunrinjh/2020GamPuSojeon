#pragma once
#include <iostream>
using namespace std;
class Car
{
public:
	int getSpeed();
	void setSpeed(int s);
	void honk();
private:
	int speed;
};

