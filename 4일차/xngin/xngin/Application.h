#pragma once
#include <Windows.h>
#include "Scene.h"
class Application
{
private:
	LARGE_INTEGER beforeInterval, currentInterval, Frequency;
public:
	Application();
	~Application();

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	HWND FloatWindow(HINSTANCE hInstance, int cmdShow);

	void InitWindow(HINSTANCE hInstance);
	void InitD3D(HWND hWnd);
	void InitDeltaTime();
	void InitManager();

	void ReleaseD3D();
	void DeleteManager();

	int DoMainLoop(Scene* firstScene);
	
	float getDeltaTime();
};

