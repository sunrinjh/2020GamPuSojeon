#include "stdafx.h"
#include "FontExample.h"

/*--------------------------------------------------------------------------------*/
//
//							생성자 부분에서 변수 초기화
//
/*--------------------------------------------------------------------------------*/
FontExample::FontExample() {
	//폰트의 크기와 처음에 들어갈 문자열을 넣는다.
	m_pFont_1 = new ZeroFont(30, "처음 문자열1");
	//까만색으로 설정
	m_pFont_1->SetColor(0xff000000);
	PushScene(m_pFont_1);

	//폰트의 크기와 처음에 들어갈 문자열을 넣는다.
	m_pFont_2 = new ZeroFont(20, "처음 문자열2", "나눔고딕");
	//SetWeight 함수로 굵기를 지정할 수 있다. 이용 가능한 값은 100부터 900까지 100 단위.
	//굵기 값을 주지 않으면 일반 굵기인 400으로 설정된다.
	m_pFont_2->SetWeight(900);

	//빨간색으로 설정
	m_pFont_2->SetColor(0xffff0000);
	m_pFont_2->SetPos(0, 100);
	PushScene(m_pFont_2);

	//폰트의 크기와 처음에 들어갈 문자열을 넣는다.
	m_pFont_3 = new ZeroFont(50, "처음 문자열3");
	m_pFont_3->SetColor(0xff33dd33);
	m_pFont_3->SetPos(0, 200);
	PushScene(m_pFont_3);

	//네 번째 인자를 통해 설치하지 않은 글꼴도 사용할 수 있다.
	m_pFont_4 = new ZeroFont(70, "Use font without installation", "BELLABOO", "Texture/Font/BELLABOO.ttf");
	m_pFont_4->SetColor(0xff28C0D8);
	m_pFont_4->SetPos(0, 500);
	PushScene(m_pFont_4);
}
/*--------------------------------------------------------------------------------*/
//
//										소멸자
//
/*--------------------------------------------------------------------------------*/
FontExample::~FontExample() {
}
/*--------------------------------------------------------------------------------*/
//
//							Update 함수에서는 기능을 검사
//
/*--------------------------------------------------------------------------------*/
void FontExample::Update(float eTime) {
	ZeroIScene::Update(eTime);

	//StartToCurrentTime()함수는 이 클래스가 생성된 후 지난 시간 초를 의미한다.
	//즉 SetString 함수는 문자열뿐만 아니라 int형을 받으면 알아서 문자열로 변환하여 출력해준다.
	m_pFont_2->SetString((int) StartToCurrentTime());

	m_pFont_3->SetString("printf()함수처럼 값을 받자\n%s, %.1f",
						 "송희문의 뇌 반지름의 길이는", 0.5f);

	if (ZeroInputMgr->GetKey('1') == INPUTMGR_KEYDOWN) {
		m_pFont_3->SetWeight(100);
	}
	if (ZeroInputMgr->GetKey('2') == INPUTMGR_KEYDOWN) {
		m_pFont_3->SetWeight(200);
	}
	if (ZeroInputMgr->GetKey('3') == INPUTMGR_KEYDOWN) {
		m_pFont_3->SetWeight(300);
	}
	if (ZeroInputMgr->GetKey('4') == INPUTMGR_KEYDOWN) {
		m_pFont_3->SetWeight(400);
	}
	if (ZeroInputMgr->GetKey('5') == INPUTMGR_KEYDOWN) {
		m_pFont_3->SetWeight(500);
	}
	if (ZeroInputMgr->GetKey('6') == INPUTMGR_KEYDOWN) {
		m_pFont_3->SetWeight(600);
	}
	if (ZeroInputMgr->GetKey('7') == INPUTMGR_KEYDOWN) {
		m_pFont_3->SetWeight(700);
	}
	if (ZeroInputMgr->GetKey('8') == INPUTMGR_KEYDOWN) {
		m_pFont_3->SetWeight(800);
	}
	if (ZeroInputMgr->GetKey('9') == INPUTMGR_KEYDOWN) {
		m_pFont_3->SetWeight(900);
	}
}
/*--------------------------------------------------------------------------------*/
//
//							Render함수에서는 그리기만 한다.
//
/*--------------------------------------------------------------------------------*/
void FontExample::Render() {
	ZeroIScene::Render();

	m_pFont_1->Render();
	m_pFont_2->Render();
	m_pFont_3->Render();
	m_pFont_4->Render();
}
