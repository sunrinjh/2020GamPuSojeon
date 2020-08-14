#pragma once

class ZeroProcessMonitor {
	// 생성자/소멸자
public:
	ZeroProcessMonitor();
	virtual ~ZeroProcessMonitor();

	// 멤버 함수
public:
	HRESULT Create();
	void Close();

	float GetCpuUsage();
	size_t GetMemoryUsage();

protected:
	HRESULT CreateCpuUsageCounter();
	void CloseCpuUsageCounter();

	// 멤버 변수
protected:
	HANDLE process;
	TCHAR processName[MAX_PATH];

	HQUERY cpuUsageQuery;
	HCOUNTER cpuUsageCounter;
};
