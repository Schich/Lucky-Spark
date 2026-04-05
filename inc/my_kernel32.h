#pragma once
#include "lucky_obf_configs.h"
#include "my_library_utils.h"
#include <windows.h>

typedef BOOL(WINAPI *_CloseHandle)(HANDLE);
typedef LPVOID(WINAPI *_ConvertThreadToFiber)(LPVOID);
typedef LPVOID(WINAPI *_CreateFiber)(SIZE_T, LPFIBER_START_ROUTINE, LPVOID);
typedef HANDLE(WINAPI *_CreateMutexA)(LPSECURITY_ATTRIBUTES, BOOL, LPCSTR);
typedef VOID(WINAPI *_DeleteCriticalSection)(LPCRITICAL_SECTION);
typedef VOID(WINAPI *_EnterCriticalSection)(LPCRITICAL_SECTION);
typedef BOOL(WINAPI *_FlushInstructionCache)(HANDLE, LPCVOID, SIZE_T);
typedef HANDLE(WINAPI *_GetCurrentProcess)(VOID);
typedef HANDLE(WINAPI *_GetCurrentThread)(VOID);
typedef DWORD(WINAPI *_GetLastError)(VOID);
typedef HMODULE(WINAPI *_GetModuleHandleW)(LPCWSTR);
typedef HMODULE(WINAPI *_GetModuleHandleA)(LPCSTR);
typedef FARPROC(WINAPI *_GetProcAddress)(HMODULE, LPCSTR);
typedef VOID(WINAPI *_GetSystemInfo)(LPSYSTEM_INFO);
typedef VOID(WINAPI *_InitializeCriticalSection)(LPCRITICAL_SECTION);
typedef BOOL(WINAPI *_IsDBCSLeadByteEx)(UINT, BYTE);
typedef VOID(WINAPI *_LeaveCriticalSection)(LPCRITICAL_SECTION);
typedef INT(WINAPI *_MultiByteToWideChar)(UINT, DWORD, LPCSTR, INT, LPWSTR, INT);
typedef LPTOP_LEVEL_EXCEPTION_FILTER(WINAPI *_SetUnhandledExceptionFilter)(LPTOP_LEVEL_EXCEPTION_FILTER);
typedef VOID(WINAPI *_Sleep)(DWORD);
typedef VOID(WINAPI *_SwitchToFiber)(LPVOID);
typedef VOID(WINAPI *_DeleteFiber)(LPVOID);
typedef LPVOID(WINAPI *_TlsGetValue)(DWORD);
typedef BOOL(WINAPI *_VirtualProtect)(LPVOID, SIZE_T, DWORD, PDWORD);
typedef SIZE_T(WINAPI *_VirtualQuery)(LPCVOID, PMEMORY_BASIC_INFORMATION, SIZE_T);
typedef INT(WINAPI *_WideCharToMultiByte)(UINT, DWORD, LPCWSTR, INT, LPSTR, INT, LPCSTR, LPBOOL);
typedef PVOID(WINAPI *_AddVectoredExceptionHandler)(ULONG FirstHandler, PVECTORED_EXCEPTION_HANDLER Handler);
typedef HANDLE(WINAPI *_CreateThread)(LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);
typedef HMODULE(WINAPI *_LoadLibraryA)(LPCSTR);

BOOL WINAPI MyCloseHandle(HANDLE hObject);
LPVOID WINAPI MyConvertThreadToFiber(LPVOID lpParameter);
LPVOID WINAPI MyCreateFiber(SIZE_T dwStackSize, LPFIBER_START_ROUTINE lpStartAddress, LPVOID lpParameter);
HANDLE WINAPI MyCreateMutexA(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCSTR lpName);
VOID WINAPI MyDeleteCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
VOID WINAPI MyEnterCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
BOOL WINAPI MyFlushInstructionCache(HANDLE hProcess, LPCVOID lpBaseAddress, SIZE_T dwSize);
HANDLE WINAPI MyGetCurrentProcess(VOID);
HANDLE WINAPI MyGetCurrentThread(VOID);
DWORD WINAPI MyGetLastError(VOID);
HMODULE WINAPI MyGetModuleHandleW(LPCWSTR lpModuleName);
HMODULE WINAPI MyGetModuleHandleA(LPCSTR lpModuleName);
FARPROC WINAPI MyGetProcAddress(HMODULE hModule, LPCSTR lpProcName);
VOID WINAPI MyGetSystemInfo(LPSYSTEM_INFO lpSystemInfo);
VOID WINAPI MyInitializeCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
BOOL WINAPI MyIsDBCSLeadByteEx(UINT CodePage, BYTE TestChar);
VOID WINAPI MyLeaveCriticalSection(LPCRITICAL_SECTION lpCriticalSection);
INT WINAPI MyMultiByteToWideChar(UINT CodePage, DWORD dwFlags, LPCSTR lpMultiByteStr, INT cbMultiByte, LPWSTR lpWideCharStr, INT cchWideChar);
LPTOP_LEVEL_EXCEPTION_FILTER WINAPI MySetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);
VOID WINAPI MySleep(DWORD dwMilliseconds);
VOID WINAPI MySwitchToFiber(LPVOID lpFiber);
VOID WINAPI MyDeleteFiber(LPVOID lpFiber);
LPVOID WINAPI MyTlsGetValue(DWORD dwTlsIndex);
BOOL WINAPI MyVirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
SIZE_T WINAPI MyVirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
INT WINAPI MyWideCharToMultiByte(UINT CodePage, DWORD dwFlags, LPCWSTR lpWideCharStr, INT cchWideChar, LPSTR lpMultiByteStr, INT cbMultiByte, LPCSTR lpDefaultChar, LPBOOL lpUsedDefaultChar);
LPVOID WINAPI MyAddVectoredExceptionHandler(ULONG FirstHandler, PVECTORED_EXCEPTION_HANDLER Handler);
HANDLE WINAPI MyCreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
HMODULE WINAPI MyLoadLibraryA(LPCSTR lpLibFileName);

// Obfuscated API names
static const unsigned char s_CloseHandle[] = {OBF_BYTE('C'), OBF_BYTE('l'), OBF_BYTE('o'), OBF_BYTE('s'), OBF_BYTE('e'), OBF_BYTE('H'), OBF_BYTE('a'), OBF_BYTE('n'), OBF_BYTE('d'), OBF_BYTE('l'), OBF_BYTE('e'), OBF_BYTE(0x00)};
static const unsigned char s_ConvertThreadToFiber[] = {OBF_BYTE('C'), OBF_BYTE('o'), OBF_BYTE('n'), OBF_BYTE('v'), OBF_BYTE('e'), OBF_BYTE('r'), OBF_BYTE('t'), OBF_BYTE('T'), OBF_BYTE('h'), OBF_BYTE('r'), OBF_BYTE('e'), OBF_BYTE('a'), OBF_BYTE('d'), OBF_BYTE('T'), OBF_BYTE('o'), OBF_BYTE('F'), OBF_BYTE('i'), OBF_BYTE('b'), OBF_BYTE('e'), OBF_BYTE('r'), OBF_BYTE(0x00)};
static const unsigned char s_CreateFiber[] = {OBF_BYTE('C'), OBF_BYTE('r'), OBF_BYTE('e'), OBF_BYTE('a'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('F'), OBF_BYTE('i'), OBF_BYTE('b'), OBF_BYTE('e'), OBF_BYTE('r'), OBF_BYTE(0x00)};
static const unsigned char s_CreateMutexA[] = {OBF_BYTE('C'), OBF_BYTE('r'), OBF_BYTE('e'), OBF_BYTE('a'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('M'), OBF_BYTE('u'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('x'), OBF_BYTE('A'), OBF_BYTE(0x00)};
static const unsigned char s_DeleteCriticalSection[] = {OBF_BYTE('D'), OBF_BYTE('e'), OBF_BYTE('l'), OBF_BYTE('e'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('C'), OBF_BYTE('r'), OBF_BYTE('i'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('c'), OBF_BYTE('a'), OBF_BYTE('l'), OBF_BYTE('S'), OBF_BYTE('e'), OBF_BYTE('c'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('o'), OBF_BYTE('n'), OBF_BYTE(0x00)};
static const unsigned char s_EnterCriticalSection[] = {OBF_BYTE('E'), OBF_BYTE('n'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('r'), OBF_BYTE('C'), OBF_BYTE('r'), OBF_BYTE('i'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('c'), OBF_BYTE('a'), OBF_BYTE('l'), OBF_BYTE('S'), OBF_BYTE('e'), OBF_BYTE('c'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('o'), OBF_BYTE('n'), OBF_BYTE(0x00)};
static const unsigned char s_FlushInstructionCache[] = {OBF_BYTE('F'), OBF_BYTE('l'), OBF_BYTE('u'), OBF_BYTE('s'), OBF_BYTE('h'), OBF_BYTE('I'), OBF_BYTE('n'), OBF_BYTE('s'), OBF_BYTE('t'), OBF_BYTE('r'), OBF_BYTE('u'), OBF_BYTE('c'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('o'), OBF_BYTE('n'), OBF_BYTE('C'), OBF_BYTE('a'), OBF_BYTE('c'), OBF_BYTE('h'), OBF_BYTE('e'), OBF_BYTE(0x00)};
static const unsigned char s_GetCurrentProcess[] = {OBF_BYTE('G'), OBF_BYTE('e'), OBF_BYTE('t'), OBF_BYTE('C'), OBF_BYTE('u'), OBF_BYTE('r'), OBF_BYTE('r'), OBF_BYTE('e'), OBF_BYTE('n'), OBF_BYTE('t'), OBF_BYTE('P'), OBF_BYTE('r'), OBF_BYTE('o'), OBF_BYTE('c'), OBF_BYTE('e'), OBF_BYTE('s'), OBF_BYTE('s'), OBF_BYTE(0x00)};
static const unsigned char s_GetCurrentThread[] = {OBF_BYTE('G'), OBF_BYTE('e'), OBF_BYTE('t'), OBF_BYTE('C'), OBF_BYTE('u'), OBF_BYTE('r'), OBF_BYTE('r'), OBF_BYTE('e'), OBF_BYTE('n'), OBF_BYTE('t'), OBF_BYTE('T'), OBF_BYTE('h'), OBF_BYTE('r'), OBF_BYTE('e'), OBF_BYTE('a'), OBF_BYTE('d'), OBF_BYTE(0x00)};
static const unsigned char s_GetLastError[] = {OBF_BYTE('G'), OBF_BYTE('e'), OBF_BYTE('t'), OBF_BYTE('L'), OBF_BYTE('a'), OBF_BYTE('s'), OBF_BYTE('t'), OBF_BYTE('E'), OBF_BYTE('r'), OBF_BYTE('r'), OBF_BYTE('o'), OBF_BYTE('r'), OBF_BYTE(0x00)};
static const unsigned char s_GetModuleHandleA[] = {OBF_BYTE('G'), OBF_BYTE('e'), OBF_BYTE('t'), OBF_BYTE('M'), OBF_BYTE('o'), OBF_BYTE('d'), OBF_BYTE('u'), OBF_BYTE('l'), OBF_BYTE('e'), OBF_BYTE('H'), OBF_BYTE('a'), OBF_BYTE('n'), OBF_BYTE('d'), OBF_BYTE('l'), OBF_BYTE('e'), OBF_BYTE('A'), OBF_BYTE(0x00)};
static const unsigned char s_GetModuleHandleW[] = {OBF_BYTE('G'), OBF_BYTE('e'), OBF_BYTE('t'), OBF_BYTE('M'), OBF_BYTE('o'), OBF_BYTE('d'), OBF_BYTE('u'), OBF_BYTE('l'), OBF_BYTE('e'), OBF_BYTE('H'), OBF_BYTE('a'), OBF_BYTE('n'), OBF_BYTE('d'), OBF_BYTE('l'), OBF_BYTE('e'), OBF_BYTE('W'), OBF_BYTE(0x00)};
static const unsigned char s_GetProcAddress[] = {OBF_BYTE('G'), OBF_BYTE('e'), OBF_BYTE('t'), OBF_BYTE('P'), OBF_BYTE('r'), OBF_BYTE('o'), OBF_BYTE('c'), OBF_BYTE('A'), OBF_BYTE('d'), OBF_BYTE('d'), OBF_BYTE('r'), OBF_BYTE('e'), OBF_BYTE('s'), OBF_BYTE('s'), OBF_BYTE(0x00)};
static const unsigned char s_GetSystemInfo[] = {OBF_BYTE('G'), OBF_BYTE('e'), OBF_BYTE('t'), OBF_BYTE('S'), OBF_BYTE('y'), OBF_BYTE('s'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('m'), OBF_BYTE('I'), OBF_BYTE('n'), OBF_BYTE('f'), OBF_BYTE('o'), OBF_BYTE(0x00)};
static const unsigned char s_InitializeCriticalSection[] = {OBF_BYTE('I'), OBF_BYTE('n'), OBF_BYTE('i'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('a'), OBF_BYTE('l'), OBF_BYTE('i'), OBF_BYTE('z'), OBF_BYTE('e'), OBF_BYTE('C'), OBF_BYTE('r'), OBF_BYTE('i'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('c'), OBF_BYTE('a'), OBF_BYTE('l'), OBF_BYTE('S'), OBF_BYTE('e'), OBF_BYTE('c'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('o'), OBF_BYTE('n'), OBF_BYTE(0x00)};
static const unsigned char s_IsDBCSLeadByteEx[] = {OBF_BYTE('I'), OBF_BYTE('s'), OBF_BYTE('D'), OBF_BYTE('B'), OBF_BYTE('C'), OBF_BYTE('S'), OBF_BYTE('L'), OBF_BYTE('e'), OBF_BYTE('a'), OBF_BYTE('d'), OBF_BYTE('B'), OBF_BYTE('y'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('E'), OBF_BYTE('x'), OBF_BYTE(0x00)};
static const unsigned char s_LeaveCriticalSection[] = {OBF_BYTE('L'), OBF_BYTE('e'), OBF_BYTE('a'), OBF_BYTE('v'), OBF_BYTE('e'), OBF_BYTE('C'), OBF_BYTE('r'), OBF_BYTE('i'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('c'), OBF_BYTE('a'), OBF_BYTE('l'), OBF_BYTE('S'), OBF_BYTE('e'), OBF_BYTE('c'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('o'), OBF_BYTE('n'), OBF_BYTE(0x00)};
static const unsigned char s_MultiByteToWideChar[] = {OBF_BYTE('M'), OBF_BYTE('u'), OBF_BYTE('l'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('B'), OBF_BYTE('y'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('T'), OBF_BYTE('o'), OBF_BYTE('W'), OBF_BYTE('i'), OBF_BYTE('d'), OBF_BYTE('e'), OBF_BYTE('C'), OBF_BYTE('h'), OBF_BYTE('a'), OBF_BYTE('r'), OBF_BYTE(0x00)};
static const unsigned char s_SetUnhandledExceptionFilter[] = {OBF_BYTE('S'), OBF_BYTE('e'), OBF_BYTE('t'), OBF_BYTE('U'), OBF_BYTE('n'), OBF_BYTE('h'), OBF_BYTE('a'), OBF_BYTE('n'), OBF_BYTE('d'), OBF_BYTE('l'), OBF_BYTE('e'), OBF_BYTE('d'), OBF_BYTE('E'), OBF_BYTE('x'), OBF_BYTE('c'), OBF_BYTE('e'), OBF_BYTE('p'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('o'), OBF_BYTE('n'), OBF_BYTE('F'), OBF_BYTE('i'), OBF_BYTE('l'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('r'), OBF_BYTE(0x00)};
static const unsigned char s_Sleep[] = {OBF_BYTE('S'), OBF_BYTE('l'), OBF_BYTE('e'), OBF_BYTE('e'), OBF_BYTE('p'), OBF_BYTE(0x00)};
static const unsigned char s_SwitchToFiber[] = {OBF_BYTE('S'), OBF_BYTE('w'), OBF_BYTE('i'), OBF_BYTE('t'), OBF_BYTE('c'), OBF_BYTE('h'), OBF_BYTE('T'), OBF_BYTE('o'), OBF_BYTE('F'), OBF_BYTE('i'), OBF_BYTE('b'), OBF_BYTE('e'), OBF_BYTE('r'), OBF_BYTE(0x00)};
static const unsigned char s_TlsGetValue[] = {OBF_BYTE('T'), OBF_BYTE('l'), OBF_BYTE('s'), OBF_BYTE('G'), OBF_BYTE('e'), OBF_BYTE('t'), OBF_BYTE('V'), OBF_BYTE('a'), OBF_BYTE('l'), OBF_BYTE('u'), OBF_BYTE('e'), OBF_BYTE(0x00)};
static const unsigned char s_VirtualProtect[] = {OBF_BYTE('V'), OBF_BYTE('i'), OBF_BYTE('r'), OBF_BYTE('t'), OBF_BYTE('u'), OBF_BYTE('a'), OBF_BYTE('l'), OBF_BYTE('P'), OBF_BYTE('r'), OBF_BYTE('o'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('c'), OBF_BYTE('t'), OBF_BYTE(0x00)};
static const unsigned char s_VirtualQuery[] = {OBF_BYTE('V'), OBF_BYTE('i'), OBF_BYTE('r'), OBF_BYTE('t'), OBF_BYTE('u'), OBF_BYTE('a'), OBF_BYTE('l'), OBF_BYTE('Q'), OBF_BYTE('u'), OBF_BYTE('e'), OBF_BYTE('r'), OBF_BYTE('y'), OBF_BYTE(0x00)};
static const unsigned char s_WideCharToMultiByte[] = {OBF_BYTE('W'), OBF_BYTE('i'), OBF_BYTE('d'), OBF_BYTE('e'), OBF_BYTE('C'), OBF_BYTE('h'), OBF_BYTE('a'), OBF_BYTE('r'), OBF_BYTE('T'), OBF_BYTE('o'), OBF_BYTE('M'), OBF_BYTE('u'), OBF_BYTE('l'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('B'), OBF_BYTE('y'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE(0x00)};
static const unsigned char s_AddVectoredExceptionHandler[] = {OBF_BYTE('A'), OBF_BYTE('d'), OBF_BYTE('d'), OBF_BYTE('V'), OBF_BYTE('e'), OBF_BYTE('c'), OBF_BYTE('t'), OBF_BYTE('o'), OBF_BYTE('r'), OBF_BYTE('e'), OBF_BYTE('d'), OBF_BYTE('E'), OBF_BYTE('x'), OBF_BYTE('c'), OBF_BYTE('e'), OBF_BYTE('p'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('o'), OBF_BYTE('n'), OBF_BYTE('H'), OBF_BYTE('a'), OBF_BYTE('n'), OBF_BYTE('d'), OBF_BYTE('l'), OBF_BYTE('e'), OBF_BYTE('r'), OBF_BYTE(0x00)};
static const unsigned char s_CreateThread[] = {OBF_BYTE('C'), OBF_BYTE('r'), OBF_BYTE('e'), OBF_BYTE('a'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('T'), OBF_BYTE('h'), OBF_BYTE('r'), OBF_BYTE('e'), OBF_BYTE('a'), OBF_BYTE('d'), OBF_BYTE(0x00)};
static const unsigned char s_DeleteFiber[] = {OBF_BYTE('D'), OBF_BYTE('e'), OBF_BYTE('l'), OBF_BYTE('e'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('F'), OBF_BYTE('i'), OBF_BYTE('b'), OBF_BYTE('e'), OBF_BYTE('r'), OBF_BYTE(0x00)};
static const unsigned char s_LoadLibraryA[] = {OBF_BYTE('L'), OBF_BYTE('o'), OBF_BYTE('a'), OBF_BYTE('d'), OBF_BYTE('L'), OBF_BYTE('i'), OBF_BYTE('b'), OBF_BYTE('r'), OBF_BYTE('a'), OBF_BYTE('r'), OBF_BYTE('y'), OBF_BYTE('A'), OBF_BYTE(0x00)};
static const unsigned char s_kernel32_dll[] = {OBF_BYTE('k'), OBF_BYTE('e'), OBF_BYTE('r'), OBF_BYTE('n'), OBF_BYTE('e'), OBF_BYTE('l'), OBF_BYTE('3'), OBF_BYTE('2'), OBF_BYTE('.'), OBF_BYTE('d'), OBF_BYTE('l'), OBF_BYTE('l'), OBF_BYTE(0x00)};

