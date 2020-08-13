#pragma once

//프로그램 세팅
#define CONSOLE_ON true // 디버그 할 콘솔 켤건지 끌건지
#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define BG_COLOR D3DCOLOR_ARGB(255,255,255,255)
#define PROGRAM_NAME TEXT("Xngin")
#define CONSOLE_NAME TEXT("Xngin Console")

// 윈도우 헤더
#include <Windows.h>
#include <XAudio2.h>

// 다이렉트 X 헤더
#include <d3dx9.h>
#include<d3d9.h>

// 디버그 헤더
#include <iostream>

// 게임 매니저 헤더
#include "TextureManager.h"
#include "InputManager.h"
#include "SceneManager.h"

// 라이브러리
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9d.lib")
#pragma comment (lib, "Winmm.lib")


//상수
#define KEY_NONE 0
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_ON 3
#define SAFE_RELEASE(p) { if(p) { p->Release(); (p) = NULL; } }
#define SAFE_DELETE(p) { if(p) { delete (p); (p)=nullptr; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete [](p); (p) = nullptr; } }

//전역변수
extern LPDIRECT3D9 pd3d; // 밑으로 DirectX를 위한 변수
extern D3DPRESENT_PARAMETERS d3dpp;
extern LPDIRECT3DDEVICE9 pd3dDevice;
extern LPD3DXSPRITE pd3dSprite;
extern HWND hWnd; // Windows 창을 위한 변수
extern SceneManager* sceneManager;
extern TextureManager* textureManager;
extern InputManager* inputManager;