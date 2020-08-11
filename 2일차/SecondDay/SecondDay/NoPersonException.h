#pragma once
class NoPersonException
{
private:
	int persons;
public:
	NoPersonException(int p) : persons(p) {}
	int getPersons() { return persons; }
};

