#include "stdafx.h"
#include "AnimationExample.h"

/*--------------------------------------------------------------------------------*/
//
//							생성자 부분에서 변수 초기화
//
/*--------------------------------------------------------------------------------*/
AnimationExample::AnimationExample() {
	//5.0f의 속도로 애니메이션을 한다.
	//수치가 높아질수록 빠름
	//1.0f일 경우 1초에 한장씩 애니메이션함
	//(그러면 5.0f일 경우는 1초에 5장넘어가겟죠)
	m_pAni = new ZeroAnimation(5.0f);
	PushScene(m_pAni);

	//이거 그림 그리느라 개힘듬 ㅋ
	for (int i = 0; i < 4; i++)
		m_pAni->PushSprite("Texture/Monster/Idle_%d.png", i);
}
/*--------------------------------------------------------------------------------*/
//
//										소멸자
//
/*--------------------------------------------------------------------------------*/
AnimationExample::~AnimationExample() {
}
/*--------------------------------------------------------------------------------*/
//
//							Update 함수에서는 기능을 검사
//
/*--------------------------------------------------------------------------------*/
void AnimationExample::Update(float eTime) {
	ZeroIScene::Update(eTime);

	if (ZeroInputMgr->GetKey('A') == INPUTMGR_KEYON)
		m_pAni->AddPosX(-300 * eTime);
	if (ZeroInputMgr->GetKey('D') == INPUTMGR_KEYON)
		m_pAni->AddPosX(300 * eTime);
	if (ZeroInputMgr->GetKey('W') == INPUTMGR_KEYON)
		m_pAni->AddPosY(-300 * eTime);
	if (ZeroInputMgr->GetKey('S') == INPUTMGR_KEYON)
		m_pAni->AddPosY(300 * eTime);
}
/*--------------------------------------------------------------------------------*/
//
//							Render함수에서는 그리기만 한다.
//
/*--------------------------------------------------------------------------------*/
void AnimationExample::Render() {
	ZeroIScene::Render();
	m_pAni->Render();
}
