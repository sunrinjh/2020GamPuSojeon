#pragma once

#include "ZeroMathManager.h"

class ZeroRegulator {
private:
	float updatePeriod;
	DWORD nextUpdateTime;

public:
	ZeroRegulator(float _updatePerSecond) {
		nextUpdateTime = (DWORD)(timeGetTime() + ZeroMathMgr->RandFloat(0, 1) * 1000);

		if (_updatePerSecond > 0)
			updatePeriod = 1000.0f / _updatePerSecond;
		else if (_updatePerSecond < 0)
			updatePeriod = -1.0f;
		else
			updatePeriod = 0.0f;
	}

	bool IsReady() {
		if (updatePeriod == 0) return true;
		if (updatePeriod < 0) return false;

		DWORD dwCurrentTime = timeGetTime();

		// 변화를 주기 위한 아주 조그마한 수
		static const float UpdatePeriodVariator = 10.0f;

		if (dwCurrentTime > nextUpdateTime) {
			nextUpdateTime =
			    (DWORD)(dwCurrentTime + updatePeriod +
			            ZeroMathMgr->RandFloat(-UpdatePeriodVariator, UpdatePeriodVariator));
			return true;
		}

		return false;
	}
};
