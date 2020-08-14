#include "stdafx.h"
#include "ShaderExample.h"

/*--------------------------------------------------------------------------------*/
//
//							생성자 부분에서 변수 초기화
//
/*--------------------------------------------------------------------------------*/
ShaderExample::ShaderExample() {
}
/*--------------------------------------------------------------------------------*/
//
//										소멸자
//
/*--------------------------------------------------------------------------------*/
ShaderExample::~ShaderExample() {
}
/*--------------------------------------------------------------------------------*/
//
//							Update 함수에서는 기능을 검사
//
/*--------------------------------------------------------------------------------*/
void ShaderExample::Update(float eTime) {
	ZeroIScene::Update(eTime);

	if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYON) {
		ZeroParticleSprite* p = new ZeroParticleSprite("Texture/Particle.png", 20);
		p->SetPos(ZeroInputMgr->GetClientPoint() - ZeroVec(p->Width() / 2, p->Height() / 2));
		p->SetScalingCenter(p->Width() / 2, p->Height() / 2);
		p->SetParticleColorStart(255, 255, 0, 0);
		p->SetParticleColorEnd(0, 255, 255, 255);
		p->SetParticleSpread(360);
		p->SetParticleLifeTime(1, 3);
		p->SetParticleScale(0.05, 0.15);
		p->SetParticleSpeed(100, 200);
		p->SetRenderPage(1);
		p->SetRenderState(SPRITEMGR_LIGHTEN);	//이게 추가됨
		PushScene(p);
		p->Start();
	}

	//스페이스 바를 누르면 셰이더 적용
	if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYDOWN) {
		//shader라는 이름의 텍스쳐에 3초동안 EdgeDetect 셰이더 적용
		PushScene(new ZeroFxEdgeDetect(3.0f, "shader"));
	}
}
/*--------------------------------------------------------------------------------*/
//
//							Render함수에서는 그리기만 한다.
//
/*--------------------------------------------------------------------------------*/
void ShaderExample::Render() {
	ZeroIScene::Render();

	//아까 "shader" 텍스쳐에 셰이더 적용했으니 여기서 그림 그림
	ZeroRTMgr("shader")->Begin();
	ZeroEffectMgr->RenderPage(1);
	ZeroRTMgr("shader")->End();
	ZeroRTMgr("shader")->Render();
}
