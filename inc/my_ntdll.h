#pragma once
#include "my_kernel32.h"
#include "my_library_utils.h"
#include <windows.h>

typedef NTSTATUS(WINAPI *_NtAllocateVirtualMemory)(HANDLE, PVOID *, ULONG_PTR, PSIZE_T, ULONG, ULONG);
typedef NTSTATUS(WINAPI *_NtProtectVirtualMemory)(HANDLE, PVOID *, PSIZE_T, ULONG, PULONG);
typedef NTSTATUS(WINAPI *_NtFreeVirtualMemory)(HANDLE, PVOID *, PSIZE_T, ULONG);
typedef NTSTATUS(WINAPI *_NtSetInformationThread)(HANDLE, int, PVOID, ULONG);
typedef NTSTATUS(WINAPI *_NtDelayExecution)(BOOL, PLARGE_INTEGER);
typedef NTSTATUS(NTAPI *_NtCreateThreadEx)(PHANDLE, ACCESS_MASK, PVOID, HANDLE, PVOID, PVOID, ULONG, SIZE_T, SIZE_T, SIZE_T, PVOID);

NTSTATUS WINAPI MyNtAllocateVirtualMemory(HANDLE ProcessHandle, PVOID *BaseAddress, ULONG_PTR ZeroBits, PSIZE_T RegionSize, ULONG AllocationType, ULONG Protect);
NTSTATUS WINAPI MyNtProtectVirtualMemory(HANDLE ProcessHandle, PVOID *BaseAddress, PSIZE_T RegionSize, ULONG NewProtect, PULONG OldProtect);
NTSTATUS WINAPI MyNtFreeVirtualMemory(HANDLE ProcessHandle, PVOID *BaseAddress, PSIZE_T RegionSize, ULONG FreeType);
NTSTATUS WINAPI MyNtSetInformationThread(HANDLE ThreadHandle, int ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength);
NTSTATUS WINAPI MyNtDelayExecution(BOOL Alertable, PLARGE_INTEGER DelayInterval);
NTSTATUS WINAPI MyNtCreateThreadEx(PHANDLE a, ACCESS_MASK b, PVOID c, HANDLE d, PVOID e, PVOID f, ULONG g, SIZE_T h, SIZE_T i, SIZE_T j, PVOID k);

// Obfuscated API names
static const unsigned char s_NtAllocateVirtualMemory[] = {OBF_BYTE('N'), OBF_BYTE('t'), OBF_BYTE('A'), OBF_BYTE('l'), OBF_BYTE('l'), OBF_BYTE('o'), OBF_BYTE('c'), OBF_BYTE('a'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('V'), OBF_BYTE('i'), OBF_BYTE('r'), OBF_BYTE('t'), OBF_BYTE('u'), OBF_BYTE('a'), OBF_BYTE('l'), OBF_BYTE('M'), OBF_BYTE('e'), OBF_BYTE('m'), OBF_BYTE('o'), OBF_BYTE('r'), OBF_BYTE('y'), OBF_BYTE(0x00)};
static const unsigned char s_NtProtectVirtualMemory[] = {OBF_BYTE('N'), OBF_BYTE('t'), OBF_BYTE('P'), OBF_BYTE('r'), OBF_BYTE('o'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('c'), OBF_BYTE('t'), OBF_BYTE('V'), OBF_BYTE('i'), OBF_BYTE('r'), OBF_BYTE('t'), OBF_BYTE('u'), OBF_BYTE('a'), OBF_BYTE('l'), OBF_BYTE('M'), OBF_BYTE('e'), OBF_BYTE('m'), OBF_BYTE('o'), OBF_BYTE('r'), OBF_BYTE('y'), OBF_BYTE(0x00)};
static const unsigned char s_NtFreeVirtualMemory[] = {OBF_BYTE('N'), OBF_BYTE('t'), OBF_BYTE('F'), OBF_BYTE('r'), OBF_BYTE('e'), OBF_BYTE('e'), OBF_BYTE('V'), OBF_BYTE('i'), OBF_BYTE('r'), OBF_BYTE('t'), OBF_BYTE('u'), OBF_BYTE('a'), OBF_BYTE('l'), OBF_BYTE('M'), OBF_BYTE('e'), OBF_BYTE('m'), OBF_BYTE('o'), OBF_BYTE('r'), OBF_BYTE('y'), OBF_BYTE(0x00)};
static const unsigned char s_NtSetInformationThread[] = {OBF_BYTE('N'), OBF_BYTE('t'), OBF_BYTE('S'), OBF_BYTE('e'), OBF_BYTE('t'), OBF_BYTE('I'), OBF_BYTE('n'), OBF_BYTE('f'), OBF_BYTE('o'), OBF_BYTE('r'), OBF_BYTE('m'), OBF_BYTE('a'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('o'), OBF_BYTE('n'), OBF_BYTE('T'), OBF_BYTE('h'), OBF_BYTE('r'), OBF_BYTE('e'), OBF_BYTE('a'), OBF_BYTE('d'), OBF_BYTE(0x00)};
static const unsigned char s_NtDelayExecution[] = {OBF_BYTE('N'), OBF_BYTE('t'), OBF_BYTE('D'), OBF_BYTE('e'), OBF_BYTE('l'), OBF_BYTE('a'), OBF_BYTE('y'), OBF_BYTE('E'), OBF_BYTE('x'), OBF_BYTE('e'), OBF_BYTE('c'), OBF_BYTE('u'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('o'), OBF_BYTE('n'), OBF_BYTE(0x00)};
static const unsigned char s_ntdll_dll[] = {OBF_BYTE('n'), OBF_BYTE('t'), OBF_BYTE('d'), OBF_BYTE('l'), OBF_BYTE('l'), OBF_BYTE('.'), OBF_BYTE('d'), OBF_BYTE('l'), OBF_BYTE('l'), OBF_BYTE(0x00)};
static const unsigned char s_NtCreateThreadEx[] = {OBF_BYTE('N'), OBF_BYTE('t'), OBF_BYTE('C'), OBF_BYTE('r'), OBF_BYTE('e'), OBF_BYTE('a'), OBF_BYTE('t'), OBF_BYTE('e'), OBF_BYTE('T'), OBF_BYTE('h'), OBF_BYTE('r'), OBF_BYTE('e'), OBF_BYTE('a'), OBF_BYTE('d'), OBF_BYTE('E'), OBF_BYTE('x'), OBF_BYTE(0x00)};

