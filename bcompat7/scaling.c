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

__declspec(dllexport) HRESULT WINAPI
GetDpiForMonitor(HMONITOR mon, enum MONITOR_DPI_TYPE dpiType, UINT *dpiX, UINT *dpiY)
{
	*dpiX = *dpiY = 96;
	return S_OK;
}

__declspec(dllexport) HRESULT WINAPI
SetProcessDpiAwareness(enum PROCESS_DPI_AWARENESS value)
{
	if (value != PROCESS_DPI_UNAWARE)
		SetProcessDPIAware();

	return S_OK;
}
