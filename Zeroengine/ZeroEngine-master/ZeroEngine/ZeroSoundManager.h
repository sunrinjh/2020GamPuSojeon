#pragma once

#define ZeroSoundMgr ZeroSoundManager::Instance()

class ZeroSoundManager {
private:
	ZeroSoundManager();

	FMOD::System* system;

	// map< 사운드 이름, tuple< 파일 경로, 사운드, list_tuple< 채널 이름, 채널 >, 동시 재생 제한 >>
	std::map<std::string,
	         std::tuple<std::string,
	                    FMOD::Sound*,
	                    std::list<std::tuple<std::string, FMOD::Channel*>>,
	                    int>>
	    soundList;

public:
	~ZeroSoundManager();

	static ZeroSoundManager* Instance();

	void Update(float _eTime);

	/*
	 *	사운드의 사용방식이 달라졌습니다.
	 *	사운드 사용 방식이 이제는 PushSound() -> PushChannel() -> ( PlayChannel() ) ->
	 *PauseChannel() -> ...
	 *	이런 형식으로..? 진행이 됩니다.
	*/

	// 외부 경로에서 사운드를 불러옵니다.
	// * _soundName : 사운드에 이름을 설정하여 쓸 수 있습니다.
	void PushSound(const char* _filepath, const char* _soundName);

	// 불러왔던 사운드를 삭제합니다.
	// 삭제한 사운드를 재생하던 채널도 모두 삭제됩니다.
	void PopSound(const char* _soundName);

	// 사운드를 재생시킬 채널을 생성합니다.
	// * _soundName : 채널에서 재생할 사운드의 이름입니다.
	// * _channelName : 채널에 이름을 설정하여 쓸 수 있습니다. 간단한 효과음이 아닌 이상 중복은
	// 되도록 피해주세요.
	// * isPaused : true일 경우 채널이 생성될 때 사운드가 자동으로 재생되지 않습니다.
	void PushChannel(const char* _soundName, const char* _channelName = "", bool _isPaused = false);

	// 생성된 채널을 삭제합니다.
	// * _soundName : 삭제할 채널에 사용되었던 사운드의 이름입니다.
	// * _channelName : 삭제할 채널의 이름입니다.
	// 채널에 사용된 사운드의 이름과 채널의 이름을 동시에 적는 것을 추천합니다.
	// 중복된 이름의 채널이 있을 경우 먼저 생성된 채널이 삭제됩니다.
	void PopChannel(const char* _soundName, const char* _channelName);
	void PopChannel(const char* _channelName);

	// 특정 채널을 재생시킵니다.
	void PlayChannel(const char* _channelName);
	void PlayChannel(const char* _soundName, const char* _channelName);

	// 모든 채널을 재생합니다.
	// 사운드 이름이 있을 경우 그 사운드를 담은 모든 채널만 재생합니다.
	void PlayAllChannel();
	void PlayAllChannel(const char* _soundName);

	// 특정 채널을 정지하고 삭제합니다.
	// PopChannel()과 동일합니다.
	void StopChannel(const char* _soundName, const char* _channelName);
	void StopChannel(const char* _channelName);

	// 모든 채널을 정지하고 삭제합니다.
	// 사운드 이름이 있을 경우 그 사운드를 담은 모든 채널만 정지합니다.
	void StopAllChannel();
	void StopAllChannel(const char* _soundName);

	// 특정 채널을 중지합니다.
	// 중지된 채널은 PlayChannel()로 다시 재생할 수 있습니다.
	void PauseChannel(const char* _channelName);
	void PauseChannel(const char* _soundName, const char* _channelName);

	// 모든 채널을 중지합니다.
	// 사운드 이름이 있을 경우 그 사운드를 담은 모든 채널만 중지합니다.
	void PauseAllChannel();
	void PauseAllChannel(const char* _soundName);

	// 특정 채널을 처음부터 다시 재생합니다.
	void ResetChannel(const char* _channelName);
	void ResetChannel(const char* _soundName, const char* _channelName);

	// 특정 사운드가 동시에 재생될 수 있는 수의 제한을 설정합니다.
	void SetConcurrency(const char* _soundName, int _concurrency);

	// 특정 채널의 FMOD_MODE를 설정합니다. 아래 링크를 참고하세요.
	// https://www.fmod.org/docs/content/generated/FMOD_MODE.html
	void SetChannelMode(const char* _soundName, const char* _channelName, FMOD_MODE _mode);
	void SetChannelMode(const char* _channelName, FMOD_MODE _mode);

	// おわり。
};
