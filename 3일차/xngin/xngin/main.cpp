#include "stdafx.h"
#include "Console.h"
#include "Application.h"
#include "Scene.h"
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR, INT cmdShow) {
	srand(GetTickCount());

	Console console;
	Application app;

	if (CONSOLE_OFF) {
		console.CloseConsole();
	}
	app.InitWindow(hInstance);
	app.InitD3D(app.FloatWindow(hInstance, cmdShow));

	return app.DoMainLoop(new Scene());
}
