#include "stdafx.h"
#include "SoundExample.h"

/*--------------------------------------------------------------------------------*/
//
//							생성자 부분에서 변수 초기화
//
/*--------------------------------------------------------------------------------*/
SoundExample::SoundExample() {
	ZeroSoundMgr->PushSound("Sound/Background.wav", "배경 음악");
	ZeroSoundMgr->PushSound("Sound/Shotgun.mp3", "Shotgun");

	// 동시에 재생 가능한 채널 수를 1로 고정한다. 기본 값 및 최대 값은 256이다.
	ZeroSoundMgr->SetConcurrency(1, "배경 음악");

	status = new ZeroFont(18, "스페이스 키를 누르면 샷건 효과음 재생\n"
							  "Q 키로 BGM 재생\n"
							  "W 키로 BGM 정지\n"
							  "E 키로 BGM 다시 재생\n");
	status->SetColor(0xff000000);
}
/*--------------------------------------------------------------------------------*/
//
//										소멸자
//
/*--------------------------------------------------------------------------------*/
SoundExample::~SoundExample() {

}
/*--------------------------------------------------------------------------------*/
//
//							Update 함수에서는 기능을 검사
//
/*--------------------------------------------------------------------------------*/
void SoundExample::Update(float eTime) {
	status->Update(eTime);
	ZeroIScene::Update(eTime);

	// 샷건 효과음 재생
	if (ZeroInputMgr->GetKey(' ') == INPUTMGR_KEYDOWN)
		ZeroSoundMgr->Play("Shotgun");

	// 배경 음악 재생
	if (ZeroInputMgr->GetKey('Q') == INPUTMGR_KEYDOWN)
		ZeroSoundMgr->Play("배경 음악");

	// 배경 음악 정지
	if (ZeroInputMgr->GetKey('W') == INPUTMGR_KEYDOWN)
		ZeroSoundMgr->Stop("배경 음악");

	// 배경 음악 처음으로 되돌리기
	if (ZeroInputMgr->GetKey('E') == INPUTMGR_KEYDOWN)
		ZeroSoundMgr->Reset("배경 음악");
}
/*--------------------------------------------------------------------------------*/
//
//							Render함수에서는 그리기만 한다.
//
/*--------------------------------------------------------------------------------*/
void SoundExample::Render() {
	status->Render();
	ZeroIScene::Render();
}
