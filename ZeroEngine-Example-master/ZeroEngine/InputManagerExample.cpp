#include "stdafx.h"
#include "InputManagerExample.h"

/*--------------------------------------------------------------------------------*/
//
//							생성자 부분에서 변수 초기화
//
/*--------------------------------------------------------------------------------*/
InputManagerExample::InputManagerExample() {
	m_pSprite = new ZeroSprite("Texture/First.png");
	PushScene(m_pSprite);

	m_pTemp = new ZeroSprite("Texture/particle.png");
	m_pTemp->SetRotCenter(m_pTemp->Width() / 2, m_pTemp->Height() / 2);
	PushScene(m_pTemp);
}
/*--------------------------------------------------------------------------------*/
//
//										소멸자
//
/*--------------------------------------------------------------------------------*/
InputManagerExample::~InputManagerExample() {
}
/*--------------------------------------------------------------------------------*/
//
//							Update 함수에서는 기능을 검사
//
/*--------------------------------------------------------------------------------*/
void InputManagerExample::Update(float eTime) {
	ZeroIScene::Update(eTime);
	//m_pSprite 이동
	//키보드 값을 입력할때는 항상 대문자를 입력할 것, 소문자 입력하면 키 안받음. ㅋ
	//INPUTMGR_KEYON은 키가 눌러져있는 상태를 지속적으로 검사한다.
	if (ZeroInputMgr->GetKey('A') == INPUTMGR_KEYON)
		m_pSprite->AddPosX(-300 * eTime);
	if (ZeroInputMgr->GetKey('D') == INPUTMGR_KEYON)
		m_pSprite->AddPosX(300 * eTime);
	if (ZeroInputMgr->GetKey('W') == INPUTMGR_KEYON)
		m_pSprite->AddPosY(-300 * eTime);
	if (ZeroInputMgr->GetKey('S') == INPUTMGR_KEYON)
		m_pSprite->AddPosY(300 * eTime);

	//m_pTemp는 마우스 값을 받아 이동
	//마우스가 있는 위치로 이동시킨다.
	//INPUTMGR_KEYDOWN은 키(마우스)를 눌렀을때 딱 한번 작용한다.
	if (ZeroInputMgr->GetKey(VK_LBUTTON) == INPUTMGR_KEYDOWN)
		m_pTemp->SetPos(ZeroInputMgr->GetClientPoint());
	//위에 있는 ZeroInputMgr->GetClientPoint() 함수는 현재 마우스가 있는 좌표값을 얻어낸다.

	//m_pTemp 회전
	//INPUTMGR_KEYNONE은 키가 눌러져 있지 않으면 참이다.
	if (ZeroInputMgr->GetKey(VK_SPACE) == INPUTMGR_KEYNONE)
		m_pTemp->AddRot(60 * eTime);
}
/*--------------------------------------------------------------------------------*/
//
//							Render함수에서는 그리기만 한다.
//
/*--------------------------------------------------------------------------------*/
void InputManagerExample::Render() {
	ZeroIScene::Render();

	//m_pSprite출력후  m_pTemp를 출력하므로
	//m_pSprite와 m_pTemp가 겹쳐 있을 경우
	//m_pTemp가 m_pSprite를 덮어버린다.
	//즉, Render하는 순서를 잘 정해야한다. ㅎㅎ
	m_pSprite->Render();
	m_pTemp->Render();
}
