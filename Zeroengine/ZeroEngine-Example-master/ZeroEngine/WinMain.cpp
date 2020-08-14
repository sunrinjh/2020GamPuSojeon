#include "stdafx.h"
#include <Windows.h>
#include "Zero.h"
#include "Examples.h"

#pragma comment(lib, "comctl32")

//이 변수를 주석처리 해버리면 콘솔창 안뜬다.
ZeroConsole g_Console;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT) {
	int WindowWidth = 1024;
	int WindowHeight = 768;

	ZeroApp->RegisterWindowSize(WindowWidth, WindowHeight);
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, ZeroApp->MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"ZeroEngine", NULL };
	RegisterClassEx(&wc);

	srand(GetTickCount());

	// WS_EX_TOPMOST | WS_POPUP :: 전체화면 모드
	// WS_OVERLAPPEDWINDOW		:: 창화면 모드
	HWND hWnd = CreateWindow(L"ZeroEngine", L"ZeroEngine 예제",
							 WS_EX_TOPMOST | WS_OVERLAPPEDWINDOW, 100, 0, WindowWidth, WindowHeight,
							 GetDesktopWindow(), NULL, wc.hInstance, NULL);

	ZeroApp->SetHwnd(hWnd);

	if (SUCCEEDED(ZeroApp->InitD3D(hWnd, false))) //전체화면을 하려면 true로
	{

		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

		//여기서 처음 시작하는 Scene 정하는 것.
		//예제를 바꿔가며 실행해보자
		ZeroSceneMgr->ChangeScene(new SpriteExample());

		MSG msg;
		ZeroMemory(&msg, sizeof(msg));
		while (msg.message != WM_QUIT) {
			if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
				ZeroApp->Render();
		}
	}
	//종료
	ZeroSceneMgr->Clear();

	UnregisterClass(L"ZeroEngine", wc.hInstance);
	return 0;
}