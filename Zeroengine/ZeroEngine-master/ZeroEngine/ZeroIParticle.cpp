#include "stdafx.h"
#include "ZeroIParticle.h"
#include "ZeroApplication.h"
#include "ZeroSpriteManager.h"
#include "ZeroTextureManager.h"

ZeroIParticle::ZeroIParticle(char* _path,
                             ZeroVec _speed,
                             float _lifeTime,
                             float _size,
                             float _rotationSpeed,
                             int _colorA,
                             int _colorR,
                             int _colorG,
                             int _colorB,
                             int _renderState) {
	D3DSURFACE_DESC desc;
	texturePath = _path;
	texture = ZeroTexMgr->LoadTextureFromFile(_path);
	texture->GetLevelDesc(0, &desc);

	m_fWidth = static_cast<float>(desc.Width);
	m_fHeight = static_cast<float>(desc.Height);

	SetRect(0.0f, 0.0f, m_fWidth, m_fHeight);

	m_vScalingCenter = m_vRotCenter = ZeroVec(m_fWidth / 2.0f, m_fHeight / 2.0f);

	speed = _speed;
	lifeTime = _lifeTime;
	colorA = _colorA;
	colorR = _colorR;
	colorG = _colorG;
	colorB = _colorB;
	renderState = _renderState;
	rotationSpeed = _rotationSpeed;

	SetScale(_size, _size);

	nowLifeTime = 0.0f;
}

ZeroIParticle::~ZeroIParticle() {}

void ZeroIParticle::Render() {
	if (m_pParent == NULL) return;
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
	m_Color = D3DCOLOR_ARGB(colorA, colorR, colorG, colorB);
	ZeroSpriteMgr->Sprite()->Draw(texture, &m_Rect, NULL, NULL, m_Color);

	ZeroSpriteMgr->Sprite()->End();
}

void ZeroIParticle::Update(float _eTime) {
	ZeroIScene::Update(_eTime);

	m_vPos += speed * _eTime;
	nowLifeTime += _eTime;
	m_fRot += rotationSpeed * _eTime;
	m_Color = D3DCOLOR_ARGB(colorA, colorR, colorG, colorB);
}

void ZeroIParticle::ReloadResource() {
	texture = ZeroTexMgr->LoadTextureFromFile(const_cast<char*>(texturePath.c_str()));
}
