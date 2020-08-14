#include "stdafx.h"
#include "CameraExample.h"

/*--------------------------------------------------------------------------------*/
//
//							생성자 부분에서 변수 초기화
//
/*--------------------------------------------------------------------------------*/
CameraExample::CameraExample() {
	m_pCharacter = new ZeroAnimation(5.0f);
	PushScene(m_pCharacter);
	for (int i = 0; i < 4; i++)
		m_pCharacter->PushSprite("Texture/Monster/Idle_%d.png", i);

	m_pInterface = new ZeroSprite("Texture/Interface.png");
	//인터페이스 창은 카메라에 영향받지 않게 한다.
	m_pInterface->SetCamera(false);
	PushScene(m_pInterface);

	m_pTemp = new ZeroSprite("Texture/Particle.png");
	m_pTemp->SetPos(300, 300);
	m_pTemp->SetColor(0xffff0000);
	PushScene(m_pTemp);

	//카메라 기능을 킨다.
	ZeroCameraMgr->SetCameraOn();
	//맵 크기는 3000,3000이다.
	ZeroCameraMgr->SetScreen(3000, 3000);
	//카메라 중심은 Character이다.
	ZeroCameraMgr->SetTarget(m_pCharacter);
}
/*--------------------------------------------------------------------------------*/
//
//										소멸자
//
/*--------------------------------------------------------------------------------*/
CameraExample::~CameraExample() {
}
/*--------------------------------------------------------------------------------*/
//
//							Update 함수에서는 기능을 검사
//
/*--------------------------------------------------------------------------------*/
void CameraExample::Update(float eTime) {
	ZeroIScene::Update(eTime);

	if (ZeroInputMgr->GetKey('A') == INPUTMGR_KEYON)
		m_pCharacter->AddPosX(-300 * eTime);
	if (ZeroInputMgr->GetKey('D') == INPUTMGR_KEYON)
		m_pCharacter->AddPosX(300 * eTime);
	if (ZeroInputMgr->GetKey('W') == INPUTMGR_KEYON)
		m_pCharacter->AddPosY(-300 * eTime);
	if (ZeroInputMgr->GetKey('S') == INPUTMGR_KEYON)
		m_pCharacter->AddPosY(300 * eTime);
}
/*--------------------------------------------------------------------------------*/
//
//							Render함수에서는 그리기만 한다.
//
/*--------------------------------------------------------------------------------*/
void CameraExample::Render() {
	ZeroIScene::Render();
	m_pTemp->Render();
	m_pCharacter->Render();
	m_pInterface->Render();
}
