#include "stdafx.h"
#include <Windows.h>
#include <Zero.h>
#include "ZeroConsole.h"
#include "MainScene.h"
#include "FontExample.h"

//�� ������ �ּ�ó���ϸ� �ܼ�â �ȶ��.
ZeroConsole g_Console;

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
    int WindowWidth = 1280;
    int WindowHeight = 720;

    ZeroApp->RegisterWindowSize(WindowWidth, WindowHeight);
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, ZeroApp->MsgProc, 0L, 0L,
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      L"Engine2D", NULL };
    RegisterClassEx(&wc);

    srand(GetTickCount());

    // WS_EX_TOPMOST | WS_POPUP :: ��üȭ�� ���
    // WS_OVERLAPPEDWINDOW		:: âȭ�� ���
    HWND hWnd = CreateWindow(L"Engine2D", L"���α׷���",
        WS_OVERLAPPEDWINDOW, 100, 0, WindowWidth, WindowHeight,
        GetDesktopWindow(), NULL, wc.hInstance, NULL);

    ZeroApp->SetHwnd(hWnd);

    if (SUCCEEDED(ZeroApp->InitD3D(hWnd, false))) //��üȭ���� �Ϸ��� true��
    {

        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);

        //���⼭ ó�� �����ϴ� Scene�� ���Ѵ�
        ZeroSceneMgr->ChangeScene(new FontExample());


        MSG msg;
        ZeroMemory(&msg, sizeof(msg));
        while (msg.message != WM_QUIT)
        {
            if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else
                ZeroApp->Render();
        }
    }
    //����
    ZeroSceneMgr->Clear();

    UnregisterClass(L"Engine2D", wc.hInstance);
    return 0;
}