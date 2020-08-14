#include "stdafx.h"
#include "ParticleExample.h"

/*--------------------------------------------------------------------------------*/
//
//							생성자 부분에서 변수 초기화
//
/*--------------------------------------------------------------------------------*/
ParticleExample::ParticleExample() {

}
/*--------------------------------------------------------------------------------*/
//
//										소멸자
//
/*--------------------------------------------------------------------------------*/
ParticleExample::~ParticleExample() {
}
/*--------------------------------------------------------------------------------*/
//
//							Update 함수에서는 기능을 검사
//
/*--------------------------------------------------------------------------------*/
void ParticleExample::Update(float eTime) {
	ZeroIScene::Update(eTime);

	//파티클은 생성되었다 바로 사라지므로 따로 멤버변수에 넣어두지는 않는다.
	//파티클은 쬐끄만걸 존나 많이 생성해야 하므로 따로 설정해야 하는게 많다.
	//스페이스 바를 누르면 파티클이 생성된다.

	if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYON) {
		//프레임당 20개의 파티클을 생성한다.
		ZeroParticleSprite* p = new ZeroParticleSprite("Texture/Particle.png", 20);
		//마우스 지점에서 파티클이 생성된다.
		p->SetPos(ZeroInputMgr->GetClientPoint() - ZeroVec(p->Width() / 2, p->Height() / 2));
		//중앙에서 스케일링
		p->SetScalingCenter(p->Width() / 2, p->Height() / 2);
		//빨간색에서 시작해서
		p->SetParticleColorStart(255, 255, 0, 0);
		//하얀색으로 알파값이 0되어 투명하게 사라진다.
		p->SetParticleColorEnd(0, 255, 255, 255);
		//360도 방향으로 흩어진다.
		p->SetParticleSpread(360);
		//파티클은 최소 1초, 최대 3초동안 살아있는다.
		p->SetParticleLifeTime(1, 3);
		//파티클의 크기는 최소 0.05배, 최대 0.15배이다.
		p->SetParticleScale(0.05, 0.15);
		//파티클의 스피드는 최소 100, 최대 200이다.
		p->SetParticleSpeed(100, 200);
		//파티클을 그릴 페이지를 설정한다. 1번 페이지이다.
		p->SetRenderPage(1);
		//파티클을 계층 트리에 넣고 시작한다.
		PushScene(p);
		p->Start();
	}

	//이건 약간의 응용작~
	if (ZeroInputMgr->GetKey(VK_RBUTTON) == INPUTMGR_KEYON) {
		ZeroParticleSprite* p = new ZeroParticleSprite("Texture/Particle.png", 20);
		p->SetPos(ZeroInputMgr->GetClientPoint() - ZeroVec(p->Width() / 2, p->Height() / 2));
		p->SetScalingCenter(p->Width() / 2, p->Height() / 2);
		p->SetParticleColorStart(255, 255, 0, 0);
		p->SetParticleColorEnd(0, 255, 255, 255);
		p->SetParticleSpread(360);
		p->SetParticleLifeTime(1, 3);
		p->SetParticleScale(0.05, 0.15);
		p->SetParticleSpeed(100, 200);
		p->SetRenderPage(2);
		p->SetRenderState(SPRITEMGR_LIGHTEN);	//이게 추가됨
		PushScene(p);
		p->Start();
	}
}
/*--------------------------------------------------------------------------------*/
//
//							Render함수에서는 그리기만 한다.
//
/*--------------------------------------------------------------------------------*/
void ParticleExample::Render() {
	ZeroIScene::Render();
	//1번 페이지에서 그려지는 파티클들을 출력한다.
	//ZeroEffectMgr를 이용해야 한다.
	ZeroEffectMgr->RenderPage(1);

	ZeroRTMgr("Particle")->Begin();
	ZeroEffectMgr->RenderPage(2);
	ZeroRTMgr("Particle")->End();
	ZeroRTMgr("Particle")->Render();
}
