#include "stdafx.h"
#include "ZeroAnimation.h"

ZeroAnimation::ZeroAnimation(float _frameSpeed, bool _isLooping) {
	numberOfFrames = 0;
	framesPerSecond = static_cast<float>(_frameSpeed);
	currentFrame = 0;
	isRunning = true;
	isLooping = _isLooping;
}

ZeroAnimation::~ZeroAnimation() {
	for (auto iter = animationList.begin(); iter != animationList.end(); ++iter) {
		delete *iter;
	}
	animationList.clear();
}

void ZeroAnimation::PushSprite(char* _imageFilePath, ...) {
	char buffer[256] = { 0 };
	char* data = buffer;
	va_list vargs;
	va_start(vargs, _imageFilePath);
	int ret = vsnprintf(data, sizeof(buffer), _imageFilePath, vargs);
	va_end(vargs);
	if (ret + 1 > sizeof(buffer)) data = static_cast<char*>(malloc(ret + 1));
	va_start(vargs, _imageFilePath);
	vsprintf(data, _imageFilePath, vargs);
	va_end(vargs);

	ZeroSprite* p = new ZeroSprite(data);
	animationList.push_back(p);
	SetWidth(p->Width());
	SetHeight(p->Height());
	p->SetParent(this);
	numberOfFrames++;
	if (data != buffer) free(data);
}

void ZeroAnimation::Start() {
	isRunning = true;
}

void ZeroAnimation::Stop() {
	currentFrame = 0.0f;
	isRunning = false;
}

void ZeroAnimation::Update(float _eTime) {
	ZeroIScene::Update(_eTime);
	if (isRunning) currentFrame += framesPerSecond * _eTime;

	if (static_cast<int>(currentFrame) >= numberOfFrames) {
		if (isLooping)
			currentFrame = 0;
		else
			currentFrame = static_cast<float>(numberOfFrames);
	}
}

void ZeroAnimation::Render() {
	if (numberOfFrames == 0) return;
	ZeroIScene::Render();

	if (static_cast<int>(currentFrame) == numberOfFrames)
		animationList[static_cast<int>(currentFrame - 1)]->Render();
	else
		animationList[static_cast<int>(currentFrame)]->Render();
}

int ZeroAnimation::NumberOfFrames() const {
	return numberOfFrames;
}

float ZeroAnimation::FramesPerSecond() const {
	return framesPerSecond;
}

void ZeroAnimation::SetFramesPerSecond(float _framesPerSecond) {
	framesPerSecond = _framesPerSecond;
}

int ZeroAnimation::CurrentFrame() const {
	return int(currentFrame);
}

void ZeroAnimation::SetCurrentFrame(int _currentFrame) {
	currentFrame = float(_currentFrame);
}

bool ZeroAnimation::IsRunning() const {
	return isRunning;
}

void ZeroAnimation::SetRunning(bool _isRunning) {
	isRunning = _isRunning;
}

bool ZeroAnimation::IsLooping() const {
	return isLooping;
}

void ZeroAnimation::SetLooping(bool _isLooping) {
	isLooping = _isLooping;
}
