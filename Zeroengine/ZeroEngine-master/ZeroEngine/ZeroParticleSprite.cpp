#include "stdafx.h"
#include "ZeroParticleSprite.h"
#include "ZeroEffectManager.h"
#include "ZeroMathManager.h"
#include "ZeroSpriteManager.h"
#include "ZeroTextureManager.h"

ZeroParticleSprite::ZeroParticleSprite(const char* _path, int _size) {
	count = 0;
	time = 0.0f;
	renderState = SPRITEMGR_NORMAL;
	direction = 0.0f;

	path = const_cast<char*>(_path);
	size = _size;

	spread = 360.0f;
	rotSpeed = 60.0f;

	LPDIRECT3DTEXTURE9 texture;
	D3DSURFACE_DESC desc;
	texture = ZeroTexMgr->LoadTextureFromFile(_path);
	texture->GetLevelDesc(0, &desc);

	m_fWidth = static_cast<float>(desc.Width);
	m_fHeight = static_cast<float>(desc.Height);

	SetParticleColorStart(255, 255, 255, 255);
	SetParticleColorEnd(0, 0, 0, 0);
	SetParticleLifeTime(3.5, 4.0);
	SetParticleSpeed(0, 100);
	SetParticleScale(1.2, 2.0);

	ZeroEffectMgr->PushEffect(this);
}

ZeroParticleSprite::~ZeroParticleSprite() {
	for (PARTICLE::iterator iter = particleList.begin(); iter != particleList.end(); iter++) {
		SAFE_DELETE(*iter);
	}
	particleList.clear();

	ZeroEffectMgr->PopEffect(this);
}

void ZeroParticleSprite::PushParticle(ZeroIParticle* p) {
	particleList.push_back(p);
	p->SetParent(this);
}

void ZeroParticleSprite::CreateParticle() {
	float randspeed = ZeroMathMgr->RandFloat(minSpeed, maxSpeed);
	float randspread = ZeroMathMgr->RandFloat(direction, direction + spread) - spread / 2.0f;
	ZeroVec speed =
	    ZeroVec(randspeed * ZeroMathMgr->Cos(randspread), randspeed * ZeroMathMgr->Sin(randspread));
	float lifetime = ZeroMathMgr->RandFloat(minLifeTime, maxLifeTime);
	float size = ZeroMathMgr->RandFloat(minScale, maxScale);
	count++;

	ZeroIParticle* particle = new ZeroIParticle(path, speed, lifetime, size, rotSpeed, startA,
	                                            startR, startG, startB, renderState);
	PushParticle(particle);
	particle->Update(0);
}

void ZeroParticleSprite::Start() {
	for (int i = 0; i < size; i++) {
		CreateParticle();
	}
	SetWorldPos(Pos());
}

void ZeroParticleSprite::Update(float _eTime) {
	ZeroIScene::Update(_eTime);
	if (_eTime == 0) return;

	time += _eTime;

	for (PARTICLE::iterator iter = particleList.begin(); iter != particleList.end(); iter++) {
		(*iter)->Update(_eTime);

		if (static_cast<int>(startA +
		                     (*iter)->NowLifeTime() / (*iter)->LifeTime() * (endA - startA)) > 0) {
			(*iter)->SetColorA(static_cast<int>(
			    startA + (*iter)->NowLifeTime() / (*iter)->LifeTime() * (endA - startA)));
		}
		else if (255 - endA != 0) {
			(*iter)->SetColorA(0);
		}

		(*iter)->SetColorR(static_cast<int>(
		    startR + ((*iter)->NowLifeTime() / (*iter)->LifeTime() * (endR - startR))));
		(*iter)->SetColorG(static_cast<int>(
		    startG + ((*iter)->NowLifeTime() / (*iter)->LifeTime() * (endG - startG))));
		(*iter)->SetColorB(static_cast<int>(
		    startB + ((*iter)->NowLifeTime() / (*iter)->LifeTime() * (endB - startB))));

		if ((*iter)->NowLifeTime() >= (*iter)->LifeTime() || (*iter)->NowLifeTime() < 0) {
			SAFE_DELETE(*iter);
			iter = particleList.erase(iter);
			count--;

			if (iter == particleList.end()) break;
		}
	}
	if (count <= 0) {
		SetErase(true);
	}
}

void ZeroParticleSprite::Render() {
	ZeroIScene::Render();
	for (PARTICLE::iterator iter = particleList.begin(); iter != particleList.end(); iter++) {
		(*iter)->Render();
	}
}
