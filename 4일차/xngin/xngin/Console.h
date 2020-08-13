#pragma once
#include <io.h>
#include <fcntl.h>

class Console
{
private:
	FILE* fp;
public :
	Console();
	~Console();

	void OpenConsole();
};