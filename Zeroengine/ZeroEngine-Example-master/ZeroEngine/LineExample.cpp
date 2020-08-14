#include "stdafx.h"
#include "LineExample.h"

/*--------------------------------------------------------------------------------*/
//
//							생성자 부분에서 변수 초기화
//
/*--------------------------------------------------------------------------------*/
LineExample::LineExample() {
	m_pLine = new ZeroLine();
	//라인 굵기 5
	m_pLine->SetLineWidth(5.0f);
	//꼭지점 5개를 넣기때문에 5라고 쓰고, 5개의 ZeroVec을 넣는다.
	m_pLine->PushBackPoint(5,
						   ZeroVec(100, 100),
						   ZeroVec(200, 100),
						   ZeroVec(200, 200),
						   ZeroVec(100, 200),
						   ZeroVec(100, 100)
						   );
	//녹색 라인
	//m_pLine->SetColor( 0xff00ff00 );
	m_pLine->SetColor(D3DCOLOR_ARGB(255, 0, 255, 0));
	PushScene(m_pLine);

	m_pCircle = new ZeroLine();
	PushScene(m_pCircle);
}
/*--------------------------------------------------------------------------------*/
//
//										소멸자
//
/*--------------------------------------------------------------------------------*/
LineExample::~LineExample() {
}
/*--------------------------------------------------------------------------------*/
//
//							Update 함수에서는 기능을 검사
//
/*--------------------------------------------------------------------------------*/
void LineExample::Update(float eTime) {
	ZeroIScene::Update(eTime);
}
/*--------------------------------------------------------------------------------*/
//
//							Render함수에서는 그리기만 한다.
//
/*--------------------------------------------------------------------------------*/
void LineExample::Render() {
	ZeroIScene::Render();

	m_pLine->Render();

	//Circle은 따로 설정해놓은 ZeroVec이 없다. 그냥 Draw해버리는거임 1회용 변수지
	//원의 중심과 반지름의 길이를 넣는다.
	m_pCircle->SetColor(0xffff0000);	//빨간색
	m_pCircle->DrawCircle(ZeroVec(300, 300), 100.0f);

	//중복해서 쓸수 있다.
	m_pCircle->SetColor(0xff0000ff);	//파란색
	m_pCircle->DrawCircle(ZeroVec(500, 300), 50.0f);
}
