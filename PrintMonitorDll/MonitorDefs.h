#pragma once


#define DllExport __declspec(dllexport)
#define HKEYMONITOR HKEY

typedef struct _MONITOR2 MONITOR2;

typedef struct _MONITOR2 {
	DWORD  cbSize;
	BOOL(*pfnEnumPorts)(HANDLE hMonitor, LPWSTR pName, DWORD Level, LPBYTE pPorts, DWORD cbBuf, LPDWORD pcbNeeded, LPDWORD pcReturned);
	BOOL(*pfnOpenPort)(HANDLE hMonitor, LPWSTR pName, PHANDLE pHandle);
	BOOL(*pfnOpenPortEx)(HANDLE hMonitor, HANDLE hMonitorPort, LPWSTR pPortName, LPWSTR pPrinterName, PHANDLE pHandle, MONITOR2* pMonitor2);
	BOOL(*pfnStartDocPort)(HANDLE hPort, LPWSTR pPrinterName, DWORD JobId, DWORD Level, LPBYTE pDocInfo);
	BOOL(*pfnWritePort)(HANDLE hPort, LPBYTE pBuffer, DWORD cbBuf, LPDWORD pcbWritten);
	BOOL(*pfnReadPort)(HANDLE hPort, LPBYTE pBuffer, DWORD cbBuffer, LPDWORD pcbRead);
	BOOL(*pfnEndDocPort)(HANDLE hPort);
	BOOL(*pfnClosePort)(HANDLE hPort);
	BOOL(*pfnAddPort)(HANDLE hMonitor, LPWSTR pName, HWND hWnd, LPWSTR pMonitorName);
	BOOL(*pfnAddPortEx)(HANDLE hMonitor, LPWSTR pName, DWORD Level, LPBYTE lpBuffer, LPWSTR lpMonitorName);
	BOOL(*pfnConfigurePort)(HANDLE hMonitor, LPWSTR pName, HWND hWnd, LPWSTR pPortName);
	BOOL(*pfnDeletePort)(HANDLE hMonitor, LPWSTR pName, HWND hWnd, LPWSTR pPortName);
	BOOL(*pfnGetPrinterDataFromPort)(HANDLE hPort, DWORD ControlID, LPWSTR pValueName, LPWSTR lpInBuffer, DWORD cbInBuffer, LPWSTR lpOutBuffer, DWORD cbOutBuffer, LPDWORD lpcbReturned);
	BOOL(*pfnSetPortTimeOuts)(HANDLE hPort, LPCOMMTIMEOUTS lpCTO, DWORD reserved);
	BOOL(*pfnXcvOpenPort)(HANDLE hMonitor, LPCWSTR pszObject, ACCESS_MASK GrantedAccess, PHANDLE phXcv);
	DWORD(*pfnXcvDataPort)(HANDLE hXcv, LPCWSTR pszDataName, PBYTE pInputData, DWORD cbInputData, PBYTE pOutputData, DWORD cbOutputData, PDWORD pcbOutputNeeded);
	BOOL(*pfnXcvClosePort)(HANDLE hXcv);
	VOID(*pfnShutdown)(HANDLE hMonitor);
	DWORD(*pfnSendRecvBidiDataFromPort)(HANDLE hPort, DWORD dwAccessBit, LPCWSTR pAction, PBIDI_REQUEST_CONTAINER pReqData, PBIDI_RESPONSE_CONTAINER* ppResData);
	DWORD(*pfnNotifyUsedPorts)(HANDLE hMonitor, DWORD cPorts, PCWSTR* ppszPorts);
	DWORD(*pfnNotifyUnusedPorts)(HANDLE hMonitor, DWORD cPorts, PCWSTR* ppszPorts);
	DWORD(*pfnPowerEvent)(HANDLE hMonitor, DWORD event, POWERBROADCAST_SETTING* pSettings);
} MONITOR2, * PMONITOR2, * LPMONITOR2;


typedef struct _MONITORREG {
	DWORD cbSize;
	LONG(*fpCreateKey)(HKEYMONITOR hcKey, LPCTSTR pszSubKey, DWORD dwOptions, REGSAM samDesired, PSECURITY_ATTRIBUTES pSecurityAttributes, HKEYMONITOR* phckResult, PDWORD pdwDisposition, HANDLE hSpooler);
	LONG(*fpOpenKey)(HKEYMONITOR hcKey, LPCTSTR pszSubKey, REGSAM samDesired, HKEYMONITOR* phkResult, HANDLE hSpooler);
	LONG(*fpCloseKey)(HKEYMONITOR hcKey, HANDLE hSpooler);
	LONG(*fpDeleteKey)(HKEYMONITOR hcKey, LPCTSTR pszSubKey, HANDLE hSpooler);
	LONG(*fpEnumKey)(HKEYMONITOR hcKey, DWORD dwIndex, LPTSTR pszName, PDWORD pcchName, PFILETIME pftLastWriteTime, HANDLE hSpooler);
	LONG(*fpQueryInfoKey)(HKEYMONITOR hcKey, PDWORD pcSubKeys, PDWORD pcbKey, PDWORD pcValues, PDWORD pcbValue, PDWORD pcbData, PDWORD pcbSecurityDescriptor, PFILETIME pftLastWriteTime, HANDLE hSpooler);
	LONG(*fpSetValue)(HKEYMONITOR hcKey, LPCTSTR pszValue, DWORD dwType, const BYTE* pData, DWORD cbData, HANDLE hSpooler);
	LONG(*fpDeleteValue)(HKEYMONITOR hcKey, LPCTSTR pszValue, HANDLE hSpooler);
	LONG(*fpEnumValue)(HKEYMONITOR hcKey, DWORD dwIndex, LPTSTR pszValue, PDWORD pcbValue, PDWORD pTyp, PBYTE pData, PDWORD pcbData, HANDLE hSpooler);
	LONG(*fpQueryValue)(HKEYMONITOR hcKey, LPCTSTR pszValue, PDWORD pType, PBYTE pData, PDWORD pcbData, HANDLE hSpooler);
} MONITORREG, * PMONITORREG;

typedef struct _MONITORINIT {
	DWORD       cbSize;
	HANDLE      hSpooler;
	HKEYMONITOR hckRegistryRoot;
	PMONITORREG pMonitorReg;
	BOOL        bLocal;
	LPCWSTR     pszServerName;
} MONITORINIT, * PMONITORINIT;