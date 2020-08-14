#include "stdafx.h"
#include "ZeroSpriteManager.h"
#include "ZeroApplication.h"

ZeroSpriteManager::ZeroSpriteManager() {
	sprite = NULL;
	InitSprite();
}

ZeroSpriteManager::~ZeroSpriteManager() {
	SAFE_RELEASE(sprite);
}

ZeroSpriteManager* ZeroSpriteManager::Instance() {
	static ZeroSpriteManager instance;
	return &instance;
}

LPD3DXSPRITE ZeroSpriteManager::Sprite() const {
	return sprite;
}

void ZeroSpriteManager::ShutdownSprite() {
	SAFE_RELEASE(sprite);
}

void ZeroSpriteManager::InitSprite() {
	if (sprite) return;
	D3DXCreateSprite(ZeroApp->GetDevice(), &sprite);
}

void ZeroSpriteManager::ReloadResource() {
	ShutdownSprite();
	InitSprite();
}
