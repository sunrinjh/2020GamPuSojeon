#pragma once

#include "ZeroSprite.h"

using namespace std;

class ZeroAnimation : public ZeroIScene {
private:
	vector<ZeroSprite*> animationList;
	int numberOfFrames;
	float framesPerSecond;
	float currentFrame;
	bool isRunning;
	bool isLooping;

public:
	ZeroAnimation(float _frameSpeed, bool _isLooping = true);
	~ZeroAnimation();

	// 이 애니메이션 객체에 스프라이트를 추가합니다.
	void PushSprite(char* _imageFilePath, ...);
	// 애니메이션을 시작합니다.
	void Start();
	// 재생할 프레임의 번호를 0으로 설정하고 애니메이션을 정지합니다.
	void Stop();

	void Update(float _eTime);
	void Render();

	// 프레임의 갯수를 반환합니다.
	int NumberOfFrames() const;
	// 초당 프레임 수를 반환합니다.
	float FramesPerSecond() const;
	// 초당 프레임 수를 설정합니다.
	void SetFramesPerSecond(float _framesPerSecond);
	// 현재 재생되고 있는 프레임의 번호를 반환합니다.
	int CurrentFrame() const;
	// 현재 재생할 프레임의 번호를 설정합니다.
	void SetCurrentFrame(int _currentFrame);
	// 애니메이션이 동작하고 있는지 여부를 반환합니다.
	bool IsRunning() const;
	// 애니메이션을 재생하거나 일시정지합니다.
	void SetRunning(bool _isRunning);
	// 애니메이션이 돌아가고 있는지 여부를 반환합니다.
	bool IsLooping() const;
	// 애니메이션의 동작 여부를 설정합니다.
	void SetLooping(bool _isLooping);
};
