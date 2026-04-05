#include "my_kernel32.h"

static HINSTANCE kernel32Module = NULL;

HMODULE WINAPI MyLoadLibraryA(LPCSTR lpLibFileName) {
  static _LoadLibraryA fn = NULL;
  if (!fn)
    fn = (_LoadLibraryA)ResolveKernel32Obf(s_LoadLibraryA, &kernel32Module, s_kernel32_dll);
  return fn ? fn(lpLibFileName) : FALSE;
}

HANDLE WINAPI MyCreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId) {
  static _CreateThread fn = NULL;
  if (!fn)
    fn = (_CreateThread)ResolveKernel32Obf(s_CreateThread, &kernel32Module, s_kernel32_dll);
  return fn ? fn(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId) : FALSE;
}

BOOL WINAPI MyCloseHandle(HANDLE hObject) {
  static _CloseHandle fn = NULL;
  if (!fn)
    fn = (_CloseHandle)ResolveKernel32Obf(s_CloseHandle, &kernel32Module, s_kernel32_dll);
  return fn ? fn(hObject) : FALSE;
}

LPVOID WINAPI MyConvertThreadToFiber(LPVOID lpParameter) {
  static _ConvertThreadToFiber fn = NULL;
  if (!fn)
    fn = (_ConvertThreadToFiber)ResolveKernel32Obf(s_ConvertThreadToFiber, &kernel32Module, s_kernel32_dll);
  return fn ? fn(lpParameter) : NULL;
}

VOID WINAPI MyDeleteFiber(LPVOID lpFiber) {
  static _DeleteFiber fn = NULL;
  if (!fn)
    fn = (_DeleteFiber)ResolveKernel32Obf(s_DeleteFiber, &kernel32Module, s_kernel32_dll);
  return fn ? fn(lpFiber) : NULL;
}

LPVOID WINAPI MyCreateFiber(SIZE_T dwStackSize, LPFIBER_START_ROUTINE lpStartAddress, LPVOID lpParameter) {
  static _CreateFiber fn = NULL;
  if (!fn)
    fn = (_CreateFiber)ResolveKernel32Obf(s_CreateFiber, &kernel32Module, s_kernel32_dll);
  return fn ? fn(dwStackSize, lpStartAddress, lpParameter) : NULL;
}

HANDLE WINAPI MyCreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName) {
  static _CreateMutexA fn = NULL;
  if (!fn)
    fn = (_CreateMutexA)ResolveKernel32Obf(s_CreateMutexA, &kernel32Module, s_kernel32_dll);
  return fn ? fn(lpMutexAttributes, bInitialOwner, lpName) : NULL;
}

VOID WINAPI MyDeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
  static _DeleteCriticalSection fn = NULL;
  if (!fn)
    fn = (_DeleteCriticalSection)ResolveKernel32Obf(s_DeleteCriticalSection, &kernel32Module, s_kernel32_dll);
  if (fn)
    fn(lpCriticalSection);
}

VOID WINAPI MyEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
  static _EnterCriticalSection fn = NULL;
  if (!fn)
    fn = (_EnterCriticalSection)ResolveKernel32Obf(s_EnterCriticalSection, &kernel32Module, s_kernel32_dll);
  if (fn)
    fn(lpCriticalSection);
}

BOOL WINAPI MyFlushInstructionCache(HANDLE hProcess, LPCVOID lpBaseAddress, SIZE_T dwSize) {
  static _FlushInstructionCache fn = NULL;
  if (!fn)
    fn = (_FlushInstructionCache)ResolveKernel32Obf(s_FlushInstructionCache, &kernel32Module, s_kernel32_dll);
  return fn ? fn(hProcess, lpBaseAddress, dwSize) : FALSE;
}

HANDLE WINAPI MyGetCurrentProcess(VOID) {
  static _GetCurrentProcess fn = NULL;
  if (!fn)
    fn = (_GetCurrentProcess)ResolveKernel32Obf(s_GetCurrentProcess, &kernel32Module, s_kernel32_dll);
  return fn ? fn() : NULL;
}

HANDLE WINAPI MyGetCurrentThread(VOID) {
  static _GetCurrentThread fn = NULL;
  if (!fn)
    fn = (_GetCurrentThread)ResolveKernel32Obf(s_GetCurrentThread, &kernel32Module, s_kernel32_dll);
  return fn ? fn() : NULL;
}

DWORD WINAPI MyGetLastError(VOID) {
  static _GetLastError fn = NULL;
  if (!fn)
    fn = (_GetLastError)ResolveKernel32Obf(s_GetLastError, &kernel32Module, s_kernel32_dll);
  return fn ? fn() : 0;
}

HMODULE WINAPI MyGetModuleHandleA(LPCSTR lpLibFileName) {
  static _GetModuleHandleA fn = NULL;
  if (!fn)
    fn = (_GetModuleHandleA)ResolveKernel32Obf(s_GetModuleHandleA, &kernel32Module, s_kernel32_dll);
  return fn ? fn(lpLibFileName) : NULL;
}

HMODULE WINAPI MyGetModuleHandleW(LPCWSTR lpModuleName) {
  static _GetModuleHandleW fn = NULL;
  if (!fn)
    fn = (_GetModuleHandleW)ResolveKernel32Obf(s_GetModuleHandleW, &kernel32Module, s_kernel32_dll);
  return fn ? fn(lpModuleName) : NULL;
}

FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName) {
  static _GetProcAddress fn = NULL;
  if (!fn)
    fn = (_GetProcAddress)ResolveKernel32Obf(s_GetProcAddress, &kernel32Module, s_kernel32_dll);
  return fn ? fn(hModule, lpProcName) : NULL;
}

VOID WINAPI MyGetSystemInfo(LPSYSTEM_INFO lpSystemInfo) {
  static _GetSystemInfo fn = NULL;
  if (!fn)
    fn = (_GetSystemInfo)ResolveKernel32Obf(s_GetSystemInfo, &kernel32Module, s_kernel32_dll);
  if (fn)
    fn(lpSystemInfo);
}

VOID WINAPI MyInitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
  static _InitializeCriticalSection fn = NULL;
  if (!fn)
    fn = (_InitializeCriticalSection)ResolveKernel32Obf(s_InitializeCriticalSection, &kernel32Module, s_kernel32_dll);
  if (fn)
    fn(lpCriticalSection);
}

BOOL WINAPI MyIsDBCSLeadByteEx(UINT CodePage, BYTE TestChar) {
  static _IsDBCSLeadByteEx fn = NULL;
  if (!fn)
    fn = (_IsDBCSLeadByteEx)ResolveKernel32Obf(s_IsDBCSLeadByteEx, &kernel32Module, s_kernel32_dll);
  return fn ? fn(CodePage, TestChar) : FALSE;
}

VOID WINAPI MyLeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection) {
  static _LeaveCriticalSection fn = NULL;
  if (!fn)
    fn = (_LeaveCriticalSection)ResolveKernel32Obf(s_LeaveCriticalSection, &kernel32Module, s_kernel32_dll);
  if (fn)
    fn(lpCriticalSection);
}

INT WINAPI MyMultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, INT cbMultiByte, LPWSTR lpWideCharStr, INT cchWideChar) {
  static _MultiByteToWideChar fn = NULL;
  if (!fn)
    fn = (_MultiByteToWideChar)ResolveKernel32Obf(s_MultiByteToWideChar, &kernel32Module, s_kernel32_dll);
  return fn ? fn(CodePage, dwFlags, lpMultiByteStr, cbMultiByte, lpWideCharStr, cchWideChar) : 0;
}

LPTOP_LEVEL_EXCEPTION_FILTER WINAPI MySetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter) {
  static _SetUnhandledExceptionFilter fn = NULL;
  if (!fn)
    fn = (_SetUnhandledExceptionFilter)ResolveKernel32Obf(s_SetUnhandledExceptionFilter, &kernel32Module, s_kernel32_dll);
  return fn ? fn(lpTopLevelExceptionFilter) : NULL;
}

VOID WINAPI MySleep(DWORD dwMilliseconds) {
  static _Sleep fn = NULL;
  if (!fn)
    fn = (_Sleep)ResolveKernel32Obf(s_Sleep, &kernel32Module, s_kernel32_dll);
  if (fn)
    fn(dwMilliseconds);
}

VOID WINAPI MySwitchToFiber(LPVOID lpFiber) {
  static _SwitchToFiber fn = NULL;
  if (!fn)
    fn = (_SwitchToFiber)ResolveKernel32Obf(s_SwitchToFiber, &kernel32Module, s_kernel32_dll);
  if (fn)
    fn(lpFiber);
}

LPVOID WINAPI MyTlsGetValue(DWORD dwTlsIndex) {
  static _TlsGetValue fn = NULL;
  if (!fn)
    fn = (_TlsGetValue)ResolveKernel32Obf(s_TlsGetValue, &kernel32Module, s_kernel32_dll);
  return fn ? fn(dwTlsIndex) : NULL;
}

BOOL WINAPI MyVirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect) {
  static _VirtualProtect fn = NULL;
  if (!fn)
    fn = (_VirtualProtect)ResolveKernel32Obf(s_VirtualProtect, &kernel32Module, s_kernel32_dll);
  return fn ? fn(lpAddress, dwSize, flNewProtect, lpflOldProtect) : FALSE;
}

SIZE_T WINAPI MyVirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
  static _VirtualQuery fn = NULL;
  if (!fn)
    fn = (_VirtualQuery)ResolveKernel32Obf(s_VirtualQuery, &kernel32Module, s_kernel32_dll);
  return fn ? fn(lpAddress, lpBuffer, dwLength) : 0;
}

INT WINAPI MyWideCharToMultiByte(UINT CodePage, DWORD dwFlags, LPCWSTR lpWideCharStr, INT cchWideChar, LPSTR lpMultiByteStr, INT cbMultiByte, LPCSTR lpDefaultChar, LPBOOL lpUsedDefaultChar) {
  static _WideCharToMultiByte fn = NULL;
  if (!fn)
    fn = (_WideCharToMultiByte)ResolveKernel32Obf(s_WideCharToMultiByte, &kernel32Module, s_kernel32_dll);
  return fn ? fn(CodePage, dwFlags, lpWideCharStr, cchWideChar, lpMultiByteStr, cbMultiByte, lpDefaultChar, lpUsedDefaultChar) : 0;
}

PVOID WINAPI MyAddVectoredExceptionHandler(ULONG FirstHandler, PVECTORED_EXCEPTION_HANDLER Handler) {
  static _AddVectoredExceptionHandler fn = NULL;
  if (!fn)
    fn = (_AddVectoredExceptionHandler)ResolveKernel32Obf(s_AddVectoredExceptionHandler, &kernel32Module, s_kernel32_dll);

  return fn ? fn(FirstHandler, Handler) : NULL;
}