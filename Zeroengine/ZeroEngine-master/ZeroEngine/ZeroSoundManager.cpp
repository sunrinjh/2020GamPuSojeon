#include "stdafx.h"
#include "ZeroSoundManager.h"

#define CHANNEL_LIST(n) std::get<2>(soundList[n])

ZeroSoundManager::ZeroSoundManager() {
	FMOD::System_Create(&system);
	system->init(256, FMOD_INIT_NORMAL, NULL);
}

ZeroSoundManager::~ZeroSoundManager() {}

void ZeroSoundManager::Update(float _eTime) {
	system->update();

	for (auto iter : soundList) {
		for (auto _iter = std::get<2>(iter.second).begin();
		     _iter != std::get<2>(iter.second).end();) {
			FMOD_RESULT res = FMOD_OK;
			bool isPlaying;
			bool isPaused;
			res = std::get<1>(*_iter)->isPlaying(&isPlaying);
			std::get<1>(*_iter)->getPaused(&isPaused);

			if (res != FMOD_OK || (!isPlaying && !isPaused)) {
				PopChannel(iter.first.c_str(), std::get<0>(*_iter++).c_str());
			}
			else
				++_iter;
		}
	}
}

ZeroSoundManager* ZeroSoundManager::Instance() {
	static ZeroSoundManager instance;
	return &instance;
}

void ZeroSoundManager::PushSound(const char* _filepath, const char* _soundName) {
	for (auto iter : soundList) {
		if (std::get<0>(iter.second).compare(_filepath) == 0) {
			return;
		}
	}

	FMOD::Sound* sound;
	std::list<std::tuple<std::string, FMOD::Channel*>> tup;

	system->createSound(_filepath, FMOD_DEFAULT, 0, &sound);
	soundList[_soundName] = std::make_tuple(_filepath, sound, tup, 256);
}

void ZeroSoundManager::PopSound(const char* _soundName) {
	std::get<1>(soundList[_soundName])->release();
	soundList.erase(_soundName);
}

void ZeroSoundManager::SetConcurrency(const char* _soundName, int _concurrency) {
	std::get<3>(soundList[_soundName]) = _concurrency;
}

void ZeroSoundManager::PushChannel(const char* _soundName,
                                   const char* _channelName,
                                   bool _isPaused) {
	FMOD::Channel* channel;
	system->playSound(std::get<1>(soundList[_soundName]), 0, _isPaused, &channel);
	CHANNEL_LIST(_soundName).push_back(std::make_tuple(_channelName, channel));

	if (CHANNEL_LIST(_soundName).size() > (UINT) std::get<3>(soundList[_soundName])) {
		PopChannel(_soundName, std::get<0>(*(CHANNEL_LIST(_soundName).begin())).c_str());
	}
}

void ZeroSoundManager::PopChannel(const char* _channelName) {
	for (auto iter : soundList) {
		for (auto _iter = std::get<2>(iter.second).begin();
		     _iter != std::get<2>(iter.second).end();) {
			if (std::get<0>(*_iter).compare(_channelName) == 0) {
				std::get<1>(*_iter)->stop();
				_iter = std::get<2>(iter.second).erase(_iter);
				return;
			}
			else
				++_iter;
		}
	}
}

void ZeroSoundManager::PopChannel(const char* _soundName, const char* _channelName) {
	for (auto _iter = CHANNEL_LIST(_soundName).begin(); _iter != CHANNEL_LIST(_soundName).end();) {
		if (std::get<0>(*_iter).compare(_channelName) == 0) {
			std::get<1>(*_iter)->stop();
			_iter = CHANNEL_LIST(_soundName).erase(_iter);
			return;
		}
		else
			++_iter;
	}
}

void ZeroSoundManager::PlayChannel(const char* _channelName) {
	for (auto iter : soundList) {
		for (auto _iter : std::get<2>(iter.second)) {
			if (std::get<0>(_iter).compare(_channelName) == 0) {
				std::get<1>(_iter)->setPaused(false);
				return;
			}
		}
	}
}

void ZeroSoundManager::PlayChannel(const char* _soundName, const char* _channelName) {
	for (auto _iter = CHANNEL_LIST(_soundName).begin(); _iter != CHANNEL_LIST(_soundName).end();) {
		if (std::get<0>(*_iter).compare(_channelName) == 0) {
			std::get<1>(*_iter)->setPaused(false);
			return;
		}
		else
			++_iter;
	}
}

void ZeroSoundManager::PlayAllChannel() {
	for (auto iter : soundList) {
		for (auto _iter : std::get<2>(iter.second)) {
			std::get<1>(_iter)->setPaused(false);
		}
	}
}

void ZeroSoundManager::PlayAllChannel(const char* _soundName) {
	for (auto _iter : CHANNEL_LIST(_soundName)) {
		std::get<1>(_iter)->setPaused(false);
	}
}

void ZeroSoundManager::StopChannel(const char* _channelName) {
	PopChannel(_channelName);
}

void ZeroSoundManager::StopChannel(const char* _soundName, const char* _channelName) {
	PopChannel(_soundName, _channelName);
}

void ZeroSoundManager::StopAllChannel() {
	for (auto iter : soundList) {
		for (auto _iter = std::get<2>(iter.second).begin();
		     _iter != std::get<2>(iter.second).end();) {
			std::get<1>(*_iter)->stop();
			_iter = std::get<2>(iter.second).erase(_iter);
		}
	}
}

void ZeroSoundManager::StopAllChannel(const char* _soundName) {
	for (auto _iter = CHANNEL_LIST(_soundName).begin(); _iter != CHANNEL_LIST(_soundName).end();) {
		std::get<1>(*_iter)->stop();
		_iter = CHANNEL_LIST(_soundName).erase(_iter);
	}
}

void ZeroSoundManager::PauseChannel(const char* _channelName) {
	for (auto iter : soundList) {
		for (auto _iter : std::get<2>(iter.second)) {
			if (std::get<0>(_iter).compare(_channelName) == 0) {
				std::get<1>(_iter)->setPaused(true);
				return;
			}
		}
	}
}

void ZeroSoundManager::PauseChannel(const char* _soundName, const char* _channelName) {
	for (auto _iter = CHANNEL_LIST(_soundName).begin(); _iter != CHANNEL_LIST(_soundName).end();) {
		if (std::get<0>(*_iter).compare(_channelName) == 0) {
			std::get<1>(*_iter)->setPaused(true);
			return;
		}
		else
			++_iter;
	}
}

void ZeroSoundManager::PauseAllChannel() {
	for (auto iter : soundList) {
		for (auto _iter : std::get<2>(iter.second)) {
			std::get<1>(_iter)->setPaused(true);
		}
	}
}

void ZeroSoundManager::PauseAllChannel(const char* _soundName) {
	for (auto _iter : CHANNEL_LIST(_soundName)) {
		std::get<1>(_iter)->setPaused(true);
	}
}

void ZeroSoundManager::ResetChannel(const char* _channelName) {
	std::string sName;
	for (auto iter : soundList) {
		for (auto _iter = std::get<2>(iter.second).begin();
		     _iter != std::get<2>(iter.second).end();) {
			if (std::get<0>(*_iter).compare(_channelName) == 0) {
				sName = iter.first;
				std::get<1>(*_iter)->stop();
				_iter = std::get<2>(iter.second).erase(_iter);
				break;
			}
			else
				++_iter;
		}
	}
	PushChannel(sName.c_str(), _channelName);
}

void ZeroSoundManager::ResetChannel(const char* _soundName, const char* _channelName) {
	PopChannel(_soundName, _channelName);
	PushChannel(_soundName, _channelName);
}

void ZeroSoundManager::SetChannelMode(const char* _channelName, FMOD_MODE _mode) {
	for (auto iter : soundList) {
		for (auto _iter = std::get<2>(iter.second).begin();
		     _iter != std::get<2>(iter.second).end();) {
			if (std::get<0>(*_iter).compare(_channelName) == 0) {
				std::get<1>(*_iter)->setMode(_mode);
				return;
			}
			else
				++_iter;
		}
	}
}

void ZeroSoundManager::SetChannelMode(const char* _soundName,
                                      const char* _channelName,
                                      FMOD_MODE _mode) {
	for (auto _iter = CHANNEL_LIST(_soundName).begin(); _iter != CHANNEL_LIST(_soundName).end();) {
		if (std::get<0>(*_iter).compare(_channelName) == 0) {
			std::get<1>(*_iter)->setMode(_mode);
			return;
		}
		else
			++_iter;
	}
}
