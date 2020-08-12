#pragma once
#include <io.h>
#include <fcntl.h>

class Console
{
public :
	Console();
	~Console();

	void CloseConsole();
};