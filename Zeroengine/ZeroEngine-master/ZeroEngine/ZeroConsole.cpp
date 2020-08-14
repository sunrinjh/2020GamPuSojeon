#include "stdafx.h"
#include "ZeroConsole.h"

ZeroConsole::ZeroConsole() {
	AllocConsole();
	HANDLE stdHandle;
	int hConsole;
	FILE* fp;
	stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	hConsole = _open_osfhandle((INT_PTR) stdHandle, _O_TEXT);
	fp = _fdopen(hConsole, "w");

	freopen_s(&fp, "CONOUT$", "w", stdout);
}

ZeroConsole::~ZeroConsole() {}
