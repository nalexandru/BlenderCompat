#include <Windows.h>

__declspec(dllexport) BOOL WINAPI
GetPointerInfo(_In_ UINT32 pointerId, _Out_writes_(1) POINTER_INFO *pointerInfo)
{
	OutputDebugStringW(L"GetPointerInfo stub");
	SetLastError(ERROR_NO_DATA);
	return FALSE;
}

__declspec(dllexport) BOOL WINAPI
GetPointerInfoHistory(_In_ UINT32 pointerId, _Inout_ UINT32 *entriesCount, _Out_writes_opt_(*entriesCount) POINTER_INFO *pointerInfo)
{
	OutputDebugStringW(L"GetPointerInfoHistory stub");
	SetLastError(ERROR_NO_DATA);
	return FALSE;
}

__declspec(dllexport) BOOL WINAPI
GetPointerPenInfoHistory(_In_ UINT32 pointerId, _Inout_ UINT32 *entriesCount, _Out_writes_opt_(*entriesCount) POINTER_PEN_INFO *penInfo)
{
	OutputDebugStringW(L"GetPointerPenInfoHistory stub");
	SetLastError(ERROR_NO_DATA);
	return FALSE;
}
