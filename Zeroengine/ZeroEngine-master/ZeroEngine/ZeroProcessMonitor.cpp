#include "stdafx.h"
#include "ZeroProcessMonitor.h"
#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "pdh.lib")

// 생성자/소멸자 구현
ZeroProcessMonitor::ZeroProcessMonitor()
    : process(NULL), cpuUsageQuery(NULL), cpuUsageCounter(NULL) {
	Create();
}

ZeroProcessMonitor::~ZeroProcessMonitor() {
	Close();
}

// 멤버 함수 구현
HRESULT ZeroProcessMonitor::Create() {
	// Process 정보 열기
	DWORD dwProcessID = GetCurrentProcessId();

	process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, dwProcessID);

	if (NULL == process) {
		return E_FAIL;
	}

	// Process Instance 정보 찾음
	HMODULE hModule;
	DWORD dwNeeded;

	if (FALSE == EnumProcessModules(process, &hModule, sizeof(hModule), &dwNeeded)) {
		// TODO: 에러 처리
		// GetLastError()

		return E_FAIL;
	}

	if (0 ==
	    GetModuleBaseName(process, hModule, processName, sizeof(processName) / sizeof(TCHAR))) {
		// TODO: 에러 처리
		// GetLastError()

		return E_FAIL;
	}

	// Process 확장자 제거
	TCHAR* pPeriod = _tcschr(processName, '.');

	if (NULL != pPeriod) {
		*pPeriod = _T('\0');
	}

	// CPU 사용량 카운터 생성
	if (FAILED(CreateCpuUsageCounter())) {
		return E_FAIL;
	}

	return S_OK;
}

void ZeroProcessMonitor::Close() {
	if (NULL != process) {
		// CPU 사용량 카운터 제거
		CloseCpuUsageCounter();

		// Process 정보 닫음
		CloseHandle(process);

		process = NULL;
	}
}

float ZeroProcessMonitor::GetCpuUsage() {
	// CPU 사용량 정보 수집
	PDH_STATUS pdhStatus = PdhCollectQueryData(cpuUsageQuery);

	if (ERROR_SUCCESS != pdhStatus) {
		// TODO: 에러 처리
		// pdhStatus ==> ErrorCode

		return -1;
	}

	// CPU 사용량 정보 처리
	PDH_FMT_COUNTERVALUE fmtValue;

	pdhStatus = PdhGetFormattedCounterValue(cpuUsageCounter, PDH_FMT_DOUBLE, NULL, &fmtValue);

	if (ERROR_SUCCESS != pdhStatus) {
		// TODO: 에러 처리
		// pdhStatus ==> ErrorCode

		return -1;
	}

	return static_cast<float>(fmtValue.doubleValue);
}

size_t ZeroProcessMonitor::GetMemoryUsage() {
	// Memory 사용량 정보 처리
	PROCESS_MEMORY_COUNTERS pmc;

	if (0 == GetProcessMemoryInfo(process, &pmc, sizeof(pmc))) {
		// TODO: 에러 처리
		// GetLastError()

		return -1;
	}

	return pmc.WorkingSetSize;
}

HRESULT ZeroProcessMonitor::CreateCpuUsageCounter() {
	// PDH Query 생성
	PDH_STATUS pdhStatus = PdhOpenQuery(NULL, 0, &cpuUsageQuery);

	if (ERROR_SUCCESS != pdhStatus) {
		// TODO: 에러 처리
		// pdhStatus ==> ErrorCode

		return E_FAIL;
	}

	// CPU 사용량 Query 문자열
	TCHAR szCounterPath[MAX_PATH];

	_stprintf_s(szCounterPath, _T("\\Process(%s)\\%% Processor Time"), processName);

	// CPU 사용량 카운터 추가
	// pdhStatus = PdhAddCounter( m_hCpuUsageQuery, szCounterPath, 0, &m_hCpuUsageCounter );
	pdhStatus =
	    PdhAddCounter(cpuUsageQuery, L"\\Processor(_TOTAL)\\% Processor Time", 0, &cpuUsageCounter);
	// wprintf(L"%s\n",szCounterPath);
	if (ERROR_SUCCESS != pdhStatus) {
		// TODO: 에러 처리
		// pdhStatus ==> ErrorCode

		return E_FAIL;
	}

	pdhStatus = PdhCollectQueryData(cpuUsageQuery);

	if (ERROR_SUCCESS != pdhStatus) {
		// TODO: 에러 처리
		// pdhStatus ==> ErrorCode

		return E_FAIL;
	}

	return S_OK;
}

void ZeroProcessMonitor::CloseCpuUsageCounter() {
	// CPU 사용량 카운터 제거
	PDH_STATUS pdhStatus = PdhCloseQuery(cpuUsageQuery);
}
