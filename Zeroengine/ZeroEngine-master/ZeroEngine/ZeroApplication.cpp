#include "stdafx.h"
#include "ZeroApplication.h"

ZeroApplication::ZeroApplication() {
	D3D = NULL;
	D3D9Device = NULL;

	fps = 1.0f;
	memoryUsage = 0.0f;
	cpuUsage = 0.0f;

	windowWidth = 1024;
	windowHeight = 768;

	processCpuUsageRegulator = new ZeroRegulator(1.5f);
	processMemoryUsageRegulator = new ZeroRegulator(1.5f);
}

ZeroApplication::~ZeroApplication() {}

void ZeroApplication::Cleanup() {
	SAFE_RELEASE(D3D);
	SAFE_RELEASE(D3D9Device);
	ClearFontResource();

	SAFE_DELETE(processCpuUsageRegulator);
	SAFE_DELETE(processMemoryUsageRegulator);
}

ZeroApplication* ZeroApplication::Instance() {
	static ZeroApplication instance;
	return &instance;
}

void ZeroApplication::CalculateFPS() {
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	fps = 0.0f;
	if (times.GetCount() > 0) {
		fps = (times.GetCount() - 1) * frequency.QuadPart /
		      static_cast<float>((times.GetLast() - times.GetFirst()));
	}
}

void ZeroApplication::CalculateMemoryUsage() {
	if (processMemoryUsageRegulator->IsReady()) {
		memoryUsage = processMonitor.GetMemoryUsage() / 1024 / 1024.0f;
	}
}

void ZeroApplication::CalculateCpuUsage() {
	if (processCpuUsageRegulator->IsReady()) {
		cpuUsage = processMonitor.GetCpuUsage();
	}
}

HWND ZeroApplication::GetHwnd() const {
	return hWnd;
}

void ZeroApplication::SetHwnd(HWND _hWnd) {
	hWnd = _hWnd;
}

LPDIRECT3DDEVICE9 ZeroApplication::GetDevice() const {
	return D3D9Device;
}

float ZeroApplication::GetFPS() const {
	return fps;
}

float ZeroApplication::GetMemoryUsage() const {
	return memoryUsage;
}

float ZeroApplication::GetCpuUsage() const {
	return cpuUsage;
}

int ZeroApplication::GetWindowWidth() {
	return windowWidth;
}

int ZeroApplication::GetWindowHeight() {
	return windowHeight;
}

void ZeroApplication::RegisterWindowSize(int _windowWidth, int _windowHeight) {
	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
}

void ZeroApplication::Update(float _eTime) {
	ZeroCameraMgr->Update(_eTime);
	ZeroSceneMgr->Update(_eTime);
	ZeroSoundMgr->Update(_eTime);
	ZeroInputMgr->KeyState();
}

void ZeroApplication::Render() {
	if (CheckAndResetDevice() == false) {
		return;
	}
	if (NULL == D3D9Device) {
		return;
	}

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	times.Add(time.QuadPart);
	CalculateFPS();
	CalculateCpuUsage();
	CalculateMemoryUsage();

	if (fps > 0) {
		Update(static_cast<float>(1.0f / fps));
	}
	else {
		Update(1.0f / 60.0f);
	}

	D3D9Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 255, 255, 255), 1.0f, 0);

	if (SUCCEEDED(D3D9Device->BeginScene())) {
		ZeroSceneMgr->Render();
		D3D9Device->EndScene();
	}

	D3D9Device->Present(NULL, NULL, NULL, NULL);
}

bool ZeroApplication::CheckAndResetDevice() {
	if (D3D9Device) {
		HRESULT hr;
		hr = D3D9Device->TestCooperativeLevel();

		if (hr == D3DERR_DEVICELOST) {
			return false;
		}
		else if (hr == D3DERR_DEVICENOTRESET) {
			ZeroTexMgr->ReloadResource();
			ZeroSpriteMgr->ReloadResource();
			ZeroShaderMgr->ReloadResource();
			ZeroResourceMgr->ReloadAllResource();
			ZeroResourceMgr->OnPostDeviceReset();
			hr = D3D9Device->Reset(&D3D9DeviceProperty);
			if (SUCCEEDED(hr)) {
				ZeroResourceMgr->OnPrevDeviceReset();
				return true;
			}
			else {
				return false;
			}
		}
	}
	return true;
}

LRESULT WINAPI ZeroApplication::MsgProc(HWND _hWnd, UINT _msg, WPARAM _wParam, LPARAM _lParam) {
	LPMINMAXINFO pmmi;

	switch (_msg) {
		case WM_DESTROY:
			ZeroApp->Cleanup();
			PostQuitMessage(0);
			return 0;

		case WM_MOUSEWHEEL:
			ZeroInputMgr->WheelState(_wParam);
			return 0;

		case WM_GETMINMAXINFO:
			pmmi = (LPMINMAXINFO) _lParam;
			int frameX = GetSystemMetrics(SM_CXFRAME);
			int frameY = GetSystemMetrics(SM_CYFRAME);
			int captionY = GetSystemMetrics(SM_CYCAPTION);
			int width = ZeroApp->GetWindowWidth() + (frameX * 2) + 8;
			int height = ZeroApp->GetWindowHeight() + (frameY * 2) + captionY + 8;
			pmmi->ptMinTrackSize.x = pmmi->ptMaxTrackSize.x = width;
			pmmi->ptMinTrackSize.y = pmmi->ptMaxTrackSize.y = height;
			return 0;
	}

	return DefWindowProc(_hWnd, _msg, _wParam, _lParam);
}

HRESULT ZeroApplication::InitD3D(HWND _hWnd, bool _isFullScreen) {
	if (NULL == (D3D = Direct3DCreate9(D3D_SDK_VERSION))) return E_FAIL;

	ZeroMemory(&D3D9DeviceProperty, sizeof(D3D9DeviceProperty));
	D3D9DeviceProperty.BackBufferWidth = windowWidth;
	D3D9DeviceProperty.BackBufferHeight = windowHeight;
	D3D9DeviceProperty.Windowed = !_isFullScreen;
	D3D9DeviceProperty.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3D9DeviceProperty.BackBufferFormat = D3DFMT_A8R8G8B8;

	if (FAILED(D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd,
	                             D3DCREATE_SOFTWARE_VERTEXPROCESSING, &D3D9DeviceProperty,
	                             &D3D9Device))) {
		return E_FAIL;
	}

	return S_OK;
}

void ZeroApplication::PushFontResource(char* _fileName) {
	for (auto iter : fonts) {
		if (iter.compare(_fileName) == 0) return;
	}
	AddFontResourceExA(_fileName, FR_NOT_ENUM, NULL);
	fonts.push_back(std::string(_fileName));
}

void ZeroApplication::ClearFontResource() {
	for (auto iter : fonts) {
		RemoveFontResourceExA(iter.c_str(), FR_NOT_ENUM, NULL);
	}
	fonts.clear();
}
