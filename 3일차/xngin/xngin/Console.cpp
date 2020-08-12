#include "stdafx.h"
#include "Console.h"

Console::Console() {
	AllocConsole();

	HANDLE stdHandle;
	int hConsole;
	FILE* fp;

	stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsole = _open_osfhandle((INT_PTR)stdHandle, _O_TEXT);
	fp = _fdopen(hConsole, "w");
	freopen_s(&fp, "CONOUT$", "w", stdout);

	SetConsoleTitle(CONSOLE_NAME);
}

Console::~Console() {
	CloseConsole();
	_fcloseall();
}

void Console::CloseConsole() {
	FreeConsole();
}