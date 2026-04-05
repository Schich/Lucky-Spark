#include "my_ntdll.h"

static HMODULE ntdllModule = NULL;

NTSTATUS WINAPI MyNtCreateThreadEx(PHANDLE a, ACCESS_MASK b, PVOID c, HANDLE d, PVOID e, PVOID f, ULONG g, SIZE_T h, SIZE_T i, SIZE_T j, PVOID k) {
  static _NtCreateThreadEx fn = NULL;
  if (!fn)
    fn = (_NtCreateThreadEx)ResolveObf(s_NtCreateThreadEx, &ntdllModule, s_ntdll_dll);

  return fn ? fn(a, b, c, d, e, f, g, h, i, j, k) : -1;
}

NTSTATUS WINAPI MyNtAllocateVirtualMemory(HANDLE ProcessHandle, PVOID *BaseAddress, ULONG_PTR ZeroBits, PSIZE_T RegionSize, ULONG AllocationType, ULONG Protect) {
  static _NtAllocateVirtualMemory fn = NULL;
  if (!fn)
    fn = (_NtAllocateVirtualMemory)ResolveObf(s_NtAllocateVirtualMemory, &ntdllModule, s_ntdll_dll);

  return fn ? fn(ProcessHandle, BaseAddress, ZeroBits, RegionSize, AllocationType, Protect) : -1;
}

NTSTATUS WINAPI MyNtProtectVirtualMemory(HANDLE ProcessHandle, PVOID *BaseAddress, PSIZE_T RegionSize, ULONG NewProtect, PULONG OldProtect) {
  static _NtProtectVirtualMemory fn = NULL;
  if (!fn)
    fn = (_NtProtectVirtualMemory)ResolveObf(s_NtProtectVirtualMemory, &ntdllModule, s_ntdll_dll);

  return fn ? fn(ProcessHandle, BaseAddress, RegionSize, NewProtect, OldProtect) : -1;
}

NTSTATUS WINAPI MyNtFreeVirtualMemory(HANDLE ProcessHandle, PVOID *BaseAddress, PSIZE_T RegionSize, ULONG FreeType) {
  static _NtFreeVirtualMemory fn = NULL;
  if (!fn)
    fn = (_NtFreeVirtualMemory)ResolveObf(s_NtFreeVirtualMemory, &ntdllModule, s_ntdll_dll);

  return fn ? fn(ProcessHandle, BaseAddress, RegionSize, FreeType) : -1;
}

NTSTATUS WINAPI MyNtSetInformationThread(HANDLE ThreadHandle, int ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength) {
  static _NtSetInformationThread fn = NULL;
  if (!fn)
    fn = (_NtSetInformationThread)ResolveObf(s_NtSetInformationThread, &ntdllModule, s_ntdll_dll);

  return fn ? fn(ThreadHandle, ThreadInformationClass, ThreadInformation, ThreadInformationLength) : -1;
}

NTSTATUS WINAPI MyNtDelayExecution(BOOL Alertable, PLARGE_INTEGER DelayInterval) {
  static _NtDelayExecution fn = NULL;
  if (!fn)
    fn = (_NtDelayExecution)ResolveObf(s_NtSetInformationThread, &ntdllModule, s_ntdll_dll);

  return fn ? fn(Alertable, DelayInterval) : -1;
}