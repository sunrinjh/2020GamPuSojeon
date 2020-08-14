#include "stdafx.h"
#include "MathManagerExample.h"

/*--------------------------------------------------------------------------------*/
//
//							생성자 부분에서 변수 초기화
//
/*--------------------------------------------------------------------------------*/
MathManagerExample::MathManagerExample() {
	m_pSprite = new ZeroSprite("Texture/Rect.png");
	PushScene(m_pSprite);

	m_pRandRegulator = new ZeroRegulator(1.0f);

	m_pFont = new ZeroFont(20, "");
	m_pFont->SetColor(0xff000000);
	PushScene(m_pFont);
}
/*--------------------------------------------------------------------------------*/
//
//										소멸자
//
/*--------------------------------------------------------------------------------*/
MathManagerExample::~MathManagerExample() {
}
/*--------------------------------------------------------------------------------*/
//
//							Update 함수에서는 기능을 검사
//
/*--------------------------------------------------------------------------------*/
void MathManagerExample::Update(float eTime) {
	ZeroIScene::Update(eTime);

	static int randInt;
	static float randFloat;
	if (m_pRandRegulator->IsReady()) {
		// 0보다 크거나 같거나 10보다 작은 랜덤한 int형 수를 생성하여 반환한다.
		randInt = ZeroMathMgr->RandInt(0, 10);

		// 0보다 크거나 같거나 1보다 작은 랜덤한 float형 수를 생성하여 반환한다.
		randFloat = ZeroMathMgr->RandFloat(0, 1);
	}

	int exceedNum = 105;
	//해당 변수를 0보다 작거나 100을 넘지 않게 해준다.
	//즉 105는 100을 넘으므로 100으로 바꿔준다.
	ZeroMathMgr->Clamp(exceedNum, 0, 100);


	//10과 0 사이에 num값이 있으면 true값을, 아니면 false값을 반환한다.
	//단, num이 0과 같거나 10과 같아도 false를 반환한다.
	int num = 5;
	bool bRange = ZeroMathMgr->InRange(0, 10, num);

	//삼각함수의 cos값과 sin값을 반환한다.
	//math.h 헤더 안에 cos함수와 sin함수가 있는데도 불구하고 이렇게 따로 만든 이유는
	//기존 함수들이 개 발적화라서 따로 만들어 빠른 성능을 내게끔 만들었다.
	//고로 MathMgr안에 있는 싸인값과 코싸인값을 쓰는게 좋음 ㅎ
	m_pSprite->SetPos(
		500 + 100 * ZeroMathMgr->Cos(60 * StartToCurrentTime()),
		300 + 100 * ZeroMathMgr->Sin(60 * StartToCurrentTime())
		);		//원을 도는 공식이다. x값에 cos, y값에 sin


	//값 다 보여주기
	m_pFont->SetString(
		"randInt : %d\n"
		"randFloat : %.2f\n"
		"exceedNum : %d\n"
		"0과10 사이에 5가 %s\n"
		, randInt
		, randFloat
		, exceedNum
		, (bRange ? "있다" : "없다")
		);
}
/*--------------------------------------------------------------------------------*/
//
//							Render함수에서는 그리기만 한다.
//
/*--------------------------------------------------------------------------------*/
void MathManagerExample::Render() {
	ZeroIScene::Render();
	m_pSprite->Render();
	m_pFont->Render();
}
