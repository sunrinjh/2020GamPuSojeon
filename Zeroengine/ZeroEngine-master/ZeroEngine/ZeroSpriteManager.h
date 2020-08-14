#pragma once

#define ZeroSpriteMgr ZeroSpriteManager::Instance()

enum {
	SPRITEMGR_NORMAL,
	SPRITEMGR_LIGHTEN,
	SPRITEMGR_DARKEN,
	SPRITEMGR_MOREDARKEN,
};

class ZeroSpriteManager {
private:
	LPD3DXSPRITE sprite;

	ZeroSpriteManager();

public:
	~ZeroSpriteManager();

	static ZeroSpriteManager* Instance();

	LPD3DXSPRITE Sprite() const;

	void ShutdownSprite();
	void InitSprite();
	void ReloadResource();
};
