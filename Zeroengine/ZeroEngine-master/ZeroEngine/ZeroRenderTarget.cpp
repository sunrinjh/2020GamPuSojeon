#include "stdafx.h"
#include "ZeroRenderTarget.h"
#include "ZeroApplication.h"
#include "ZeroShaderManager.h"
#include "ZeroSprite.h"
#include "ZeroSpriteManager.h"

ZeroRenderTarget::ZeroRenderTarget() {
	texture = NULL;
	surface = NULL;
	original = NULL;
	shader = NULL;
	shaderPath = "";
	width = ZeroApp->GetWindowWidth();
	height = ZeroApp->GetWindowHeight();

	rect.Set(0, 0, width, height);

	D3DXCreateTexture(ZeroApp->GetDevice(), width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_UNKNOWN,
	                  D3DPOOL_DEFAULT, &texture);

	texture->GetSurfaceLevel(0, &surface);
}

ZeroRenderTarget::~ZeroRenderTarget() {
	SAFE_RELEASE(texture);
	SAFE_RELEASE(surface);
	SAFE_RELEASE(original);
}

void ZeroRenderTarget::Render(D3DXMATRIX* _mat /* = NULL*/) {
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	ZeroSpriteMgr->Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
	if (_mat == NULL)
		ZeroSpriteMgr->Sprite()->SetTransform(&matrix);
	else
		ZeroSpriteMgr->Sprite()->SetTransform(_mat);

	if (shader != NULL) {
		shader->Begin(NULL, 0);
		shader->BeginPass(0);
	}

	ZeroSpriteMgr->Sprite()->Draw(texture, &rect, NULL, NULL, 0xffffffff);
	ZeroSpriteMgr->Sprite()->End();

	if (shader != NULL) {
		shader->EndPass();
		shader->End();
	}
}

void ZeroRenderTarget::Update(float _eTime) {}

void ZeroRenderTarget::OnPostDeviceReset() {
	if (shader != NULL)
		shader = ZeroShaderMgr->LoadShaderFromFile(const_cast<char*>(shaderPath.c_str()));
	SAFE_RELEASE(texture);
	SAFE_RELEASE(surface);
}

void ZeroRenderTarget::OnPrevDeviceReset() {
	HRESULT hr = D3DXCreateTexture(ZeroApp->GetDevice(), width, height, 1, D3DUSAGE_RENDERTARGET,
	                               D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, &texture);
	texture->GetSurfaceLevel(0, &surface);
}

void ZeroRenderTarget::Begin(bool _clear /*=true*/) {
	ZeroApp->GetDevice()->GetRenderTarget(0, &original);
	ZeroApp->GetDevice()->SetRenderTarget(0, surface);
	if (_clear)
		ZeroApp->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0);
}

void ZeroRenderTarget::End() {
	ZeroApp->GetDevice()->SetRenderTarget(0, original);
	SAFE_RELEASE(original);
}

void ZeroRenderTarget::SetShader(const char* _path) {
	if (shader == NULL) {
		shader = ZeroShaderMgr->LoadShaderFromFile(_path);
		shaderPath = _path;
	}
}

void ZeroRenderTarget::ClearShader() {
	shader = NULL;
}

void ZeroRenderTarget::SetWidth(int width) {
	LPDIRECT3DTEXTURE9 temp = this->texture;
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	this->width = width;
	D3DXCreateTexture(ZeroApp->GetDevice(), width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_UNKNOWN,
	                  D3DPOOL_DEFAULT, &texture);
	texture->GetSurfaceLevel(0, &surface);
	this->Begin();
	ZeroSpriteMgr->Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
	ZeroSpriteMgr->Sprite()->SetTransform(&matrix);
	ZeroSpriteMgr->Sprite()->Draw(temp, &rect, NULL, NULL, 0xffffffff);
	ZeroSpriteMgr->Sprite()->End();
	this->End();
	rect.Set(0, 0, width, height);
	SAFE_RELEASE(temp);
}

void ZeroRenderTarget::SetHeight(int height) {
	LPDIRECT3DTEXTURE9 temp = this->texture;
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	this->height = height;
	D3DXCreateTexture(ZeroApp->GetDevice(), width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_UNKNOWN,
	                  D3DPOOL_DEFAULT, &texture);
	texture->GetSurfaceLevel(0, &surface);
	this->Begin();
	ZeroSpriteMgr->Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
	ZeroSpriteMgr->Sprite()->SetTransform(&matrix);
	ZeroSpriteMgr->Sprite()->Draw(temp, &rect, NULL, NULL, 0xffffffff);
	ZeroSpriteMgr->Sprite()->End();
	this->End();
	rect.Set(0, 0, width, height);
	SAFE_RELEASE(temp);
}

void ZeroRenderTarget::SetSize(int width, int height) {
	LPDIRECT3DTEXTURE9 temp = this->texture;
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	this->width = width;
	this->height = height;
	D3DXCreateTexture(ZeroApp->GetDevice(), width, height, 1, D3DUSAGE_RENDERTARGET, D3DFMT_UNKNOWN,
	                  D3DPOOL_DEFAULT, &texture);
	texture->GetSurfaceLevel(0, &surface);
	this->Begin();
	ZeroSpriteMgr->Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
	ZeroSpriteMgr->Sprite()->SetTransform(&matrix);
	ZeroSpriteMgr->Sprite()->Draw(temp, &rect, NULL, NULL, 0xffffffff);
	ZeroSpriteMgr->Sprite()->End();
	this->End();
	rect.Set(0, 0, width, height);
	SAFE_RELEASE(temp);
}
