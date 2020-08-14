#include "stdafx.h"
#include "ZeroSprite.h"
#include "ZeroApplication.h"
#include "ZeroSpriteManager.h"
#include "ZeroTextureManager.h"

ZeroSprite::ZeroSprite(const char* _path, ...) {
	char buffer[256] = { 0 };
	char* data = buffer;
	va_list vargs;
	va_start(vargs, _path);
	int ret = vsnprintf(data, sizeof(buffer), _path, vargs);
	va_end(vargs);
	if (ret + 1 > sizeof(buffer)) data = static_cast<char*>(malloc(ret + 1));
	va_start(vargs, _path);
	vsprintf(data, _path, vargs);
	va_end(vargs);

	texture = ZeroTexMgr->LoadTextureFromFile(data);
	texturePath = data;

	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);
	SetWidth(desc.Width);
	SetHeight(desc.Height);

	SetRect(0.0f, 0.0f, m_fWidth, m_fHeight);

	SetRenderState(SPRITEMGR_NORMAL);

	if (data != buffer) free(data);
}

ZeroSprite::~ZeroSprite() {}

void ZeroSprite::Render() {
	ZeroIScene::Render();

	ZeroSpriteMgr->Sprite()->SetTransform(&m_Mat);

	ZeroSpriteMgr->Sprite()->Begin(D3DXSPRITE_ALPHABLEND);

	if (RenderState() == SPRITEMGR_NORMAL) {
		ZeroApp->GetDevice()->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, true);
		ZeroApp->GetDevice()->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
		ZeroApp->GetDevice()->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
	}
	else if (RenderState() == SPRITEMGR_LIGHTEN) {
		ZeroApp->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		ZeroApp->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		ZeroApp->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else if (RenderState() == SPRITEMGR_DARKEN) {
		ZeroApp->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		ZeroApp->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		ZeroApp->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else if (RenderState() == SPRITEMGR_MOREDARKEN) {
		ZeroApp->GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		ZeroApp->GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		ZeroApp->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}
	else {
		ZeroApp->GetDevice()->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, true);
		ZeroApp->GetDevice()->SetRenderState(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
		ZeroApp->GetDevice()->SetRenderState(D3DRS_DESTBLENDALPHA, D3DBLEND_ONE);
	}

	ZeroSpriteMgr->Sprite()->Draw(texture, &m_Rect, NULL, NULL, m_Color);

	ZeroSpriteMgr->Sprite()->End();
}

void ZeroSprite::Update(float _eTime) {
	ZeroIScene::Update(_eTime);
}

void ZeroSprite::ReloadResource() {
	texture = ZeroTexMgr->LoadTextureFromFile(const_cast<char*>(texturePath.c_str()));
}
