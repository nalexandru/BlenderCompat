#include <Windows.h>

// The pointer messages (WM_POINTER*) do not exist in Windows 7.
// Because of this, it's unlikely that the GetPointer* functions will be called.

__declspec(dllexport) BOOL WINAPI
GetPointerType(_In_ UINT32 pointerId, _Out_ POINTER_INPUT_TYPE *pointerType)
{
	*pointerType = PT_MOUSE;
	return TRUE;
}

__declspec(dllexport) BOOL WINAPI
GetPointerInfo(_In_ UINT32 pointerId, _Out_writes_(1) POINTER_INFO *pointerInfo)
{
	SetLastError(ERROR_NO_DATA);
	return FALSE;
}

__declspec(dllexport) BOOL WINAPI
GetPointerInfoHistory(_In_ UINT32 pointerId, _Inout_ UINT32 *entriesCount, _Out_writes_opt_(*entriesCount) POINTER_INFO *pointerInfo)
{
	SetLastError(ERROR_NO_DATA);
	return FALSE;
}

__declspec(dllexport) BOOL WINAPI
GetPointerPenInfoHistory(_In_ UINT32 pointerId, _Inout_ UINT32 *entriesCount, _Out_writes_opt_(*entriesCount) POINTER_PEN_INFO *penInfo)
{
	SetLastError(ERROR_NO_DATA);
	return FALSE;
}

__declspec(dllexport) HANDLE WINAPI
CreateFile2(_In_ LPCWSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_ DWORD dwCreationDisposition,
	_In_opt_ LPCREATEFILE2_EXTENDED_PARAMETERS pCreateExParams)
{
	if (pCreateExParams)
		return CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, pCreateExParams->lpSecurityAttributes, dwCreationDisposition, 
			pCreateExParams->dwFileAttributes | pCreateExParams->dwFileFlags | pCreateExParams->dwSecurityQosFlags, pCreateExParams->hTemplateFile);
	else
		return CreateFileW(lpFileName, dwDesiredAccess, dwShareMode, NULL, dwCreationDisposition, 0, NULL);
}
