#include <Windows.h>

enum MONITOR_DPI_TYPE {
	MDT_EFFECTIVE_DPI,
	MDT_ANGULAR_DPI,
	MDT_RAW_DPI,
	MDT_DEFAULT
};

enum PROCESS_DPI_AWARENESS {
	PROCESS_DPI_UNAWARE,
	PROCESS_SYSTEM_DPI_AWARE,
	PROCESS_PER_MONITOR_DPI_AWARE
};

static HMODULE _kernel32, _shcore;

static BOOL(WINAPI *_GetPointerType)(_In_ UINT32, _Out_ POINTER_INPUT_TYPE *);
static BOOL(WINAPI *_GetPointerInfo)(_In_ UINT32, _Out_writes_(1) POINTER_INFO *);
static BOOL(WINAPI *_GetPointerInfoHistory)(_In_ UINT32, _Inout_ UINT32 *, POINTER_INFO *);
static BOOL(WINAPI *_GetPointerPenInfoHistory)(_In_ UINT32, _Inout_ UINT32 *, POINTER_PEN_INFO *);

static HANDLE(WINAPI *_CreateFile2)(_In_ LPCWSTR, _In_ DWORD, _In_ DWORD, _In_ DWORD, _In_opt_ LPCREATEFILE2_EXTENDED_PARAMETERS);

static HRESULT(WINAPI *_GetDpiForMonitor)(HMONITOR, enum MONITOR_DPI_TYPE, UINT *, UINT *);
static HRESULT(WINAPI *_SetProcessDpiAwareness)(enum PROCESS_DPI_AWARENESS);

// The pointer messages (WM_POINTER*) do not exist in Windows 7.
// Because of this, it's unlikely that the GetPointer* functions will be called.

__declspec(dllexport) BOOL WINAPI
GetPointerType(_In_ UINT32 pointerId, _Out_ POINTER_INPUT_TYPE *pointerType)
{
	if (_GetPointerType)
		return GetPointerType(pointerId, pointerType);

	*pointerType = PT_MOUSE;
	return TRUE;
}

__declspec(dllexport) BOOL WINAPI
GetPointerInfo(_In_ UINT32 pointerId, _Out_writes_(1) POINTER_INFO *pointerInfo)
{
	if (_GetPointerInfo)
		return _GetPointerInfo(pointerId, pointerInfo);

	SetLastError(ERROR_NO_DATA);
	return FALSE;
}

__declspec(dllexport) BOOL WINAPI
GetPointerInfoHistory(_In_ UINT32 pointerId, _Inout_ UINT32 *entriesCount, _Out_writes_opt_(*entriesCount) POINTER_INFO *pointerInfo)
{
	if (_GetPointerInfoHistory)
		return _GetPointerInfoHistory(pointerId, entriesCount, pointerInfo);

	SetLastError(ERROR_NO_DATA);
	return FALSE;
}

__declspec(dllexport) BOOL WINAPI
GetPointerPenInfoHistory(_In_ UINT32 pointerId, _Inout_ UINT32 *entriesCount, _Out_writes_opt_(*entriesCount) POINTER_PEN_INFO *penInfo)
{
	if (_GetPointerPenInfoHistory)
		return _GetPointerPenInfoHistory(pointerId, entriesCount, penInfo);

	SetLastError(ERROR_NO_DATA);
	return FALSE;
}

__declspec(dllexport) HANDLE WINAPI
CreateFile2(_In_ LPCWSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_ DWORD dwCreationDisposition,
	_In_opt_ LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams)
{
	if (_CreateFile2)
		return _CreateFile2(lpFileName, dwDesiredAccess, dwShareMode, dwCreationDisposition, pCreateExParams);

	if (pCreateExParams)
		return CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, pCreateExParams->lpSecurityAttributes, dwCreationDisposition, 
			pCreateExParams->dwFileAttributes | pCreateExParams->dwFileFlags | pCreateExParams->dwSecurityQosFlags, pCreateExParams->hTemplateFile);
	else
		return CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, NULL, dwCreationDisposition, 0, NULL);
}

__declspec(dllexport) HRESULT WINAPI
GetDpiForMonitor(HMONITOR mon, enum MONITOR_DPI_TYPE dpiType, UINT *dpiX, UINT *dpiY)
{
	if (_GetDpiForMonitor)
		return _GetDpiForMonitor(mon, dpiType, dpiX, dpiY);

	*dpiX = *dpiY = 96;
	return S_OK;
}

__declspec(dllexport) HRESULT WINAPI
SetProcessDpiAwareness(enum PROCESS_DPI_AWARENESS value)
{
	if (_SetProcessDpiAwareness)
		return _SetProcessDpiAwareness(value);

	if (value != PROCESS_DPI_UNAWARE)
		SetProcessDPIAware();

	return S_OK;
}

BOOL WINAPI
DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		_kernel32 = LoadLibrary(L"kernel32");
		_shcore = LoadLibrary(L"shcore");

		if (_kernel32) {
			_GetPointerType = GetProcAddress(_kernel32, "GetPointerType");
			_GetPointerInfo = GetProcAddress(_kernel32, "GetPointerInfo");
			_GetPointerInfoHistory = GetProcAddress(_kernel32, "GetPointerInfoHistory");
			_GetPointerPenInfoHistory = GetProcAddress(_kernel32, "GetPointerPenInfoHistory");

			_CreateFile2 = GetProcAddress(_kernel32, "CreateFile2");
		}

		if (_shcore) {
			_GetDpiForMonitor = GetProcAddress(_shcore, "GetDpiForMonitor");
			_SetProcessDpiAwareness = GetProcAddress(_shcore, "SetProcessDpiAwareness");
		}
		break;
	case DLL_PROCESS_DETACH:
		FreeLibrary(_shcore);
		FreeLibrary(_kernel32);

		break;
	}
	return TRUE;
}
