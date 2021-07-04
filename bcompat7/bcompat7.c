#include <Windows.h>

__declspec(dllexport) BOOL WINAPI
GetPointerInfo(_In_ UINT32 pointerId, _Out_writes_(1) POINTER_INFO *pointerInfo)
{
	MessageBoxA(HWND_DESKTOP, "GetPointerInfo", "API", MB_OK);
	return FALSE;
}

__declspec(dllexport) BOOL WINAPI
GetPointerInfoHistory(_In_ UINT32 pointerId, _Inout_ UINT32 *entriesCount, _Out_writes_opt_(*entriesCount) POINTER_INFO *pointerInfo)
{
	MessageBoxA(HWND_DESKTOP, "GetPointerInfoHistory", "API", MB_OK);
	return FALSE;
}

__declspec(dllexport) BOOL WINAPI
GetPointerPenInfoHistory(_In_ UINT32 pointerId, _Inout_ UINT32 *entriesCount, _Out_writes_opt_(*entriesCount) POINTER_PEN_INFO *penInfo)
{
	MessageBoxA(HWND_DESKTOP, "GetPointerPenInfoHistory", "API", MB_OK);
	return FALSE;
}
