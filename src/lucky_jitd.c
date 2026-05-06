#include "lucky_jitd.h"

volatile LONG vehLock = 0;

static LPVOID pages[3];

int vehInstalled = 0;
static SIZE_T pageSize = 0;

LPVOID ControlStart = 0;
SIZE_T ControlSize = 0;

void AcquireSpinLock() {
  while (InterlockedCompareExchange(&vehLock, 1, 0) != 0)
    YieldProcessor();
}

void ReleaseSpinLock() { InterlockedExchange(&vehLock, 0); }

static inline LPVOID AlignDown(LPVOID p) { return (LPVOID)((ULONG_PTR)p & ~(pageSize - 1)); }

void ProtectMemoryPages(LPVOID start, SIZE_T size) {
  SYSTEM_INFO si;
  MyGetSystemInfo(&si);
  pageSize = si.dwPageSize;

  ControlStart = start;
  ControlSize = size;

  for (SIZE_T offset = 0; offset < size; offset += pageSize) {

    LPVOID page = (LPBYTE)start + offset;
    page = AlignDown(page);

    SIZE_T regionSize = pageSize;
    ULONG oldProtect = 0;

    NTSTATUS status = MyNtProtectVirtualMemory(MyGetCurrentProcess(), &page, &regionSize, PAGE_EXECUTE_READ | PAGE_GUARD, &oldProtect);

    if (!NT_SUCCESS(status)) {
      __debugbreak();
      return;
    }
  }
}

void EncryptPage(void *page) {

  ULONG oldProtect;

  PVOID base = page;
  SIZE_T localSize = pageSize;
  if (!NT_SUCCESS(MyNtProtectVirtualMemory(MyGetCurrentProcess(), &base, &localSize, PAGE_READWRITE, &oldProtect))) {

    return;
  }

  uint8_t *p = (uint8_t *)base;
  for (SIZE_T i = 0; i < localSize; i += 16)
    aes128_encrypt_block(p + i, p + i, encKeys);

  if (!NT_SUCCESS(MyNtProtectVirtualMemory(MyGetCurrentProcess(), &base, &localSize, oldProtect | PAGE_GUARD, &oldProtect))) {
  }
}

void DecryptPage(void *page) {

  ULONG oldProtect;

  PVOID base = page;
  SIZE_T localSize = pageSize;
  if (!NT_SUCCESS(MyNtProtectVirtualMemory(MyGetCurrentProcess(), &base, &localSize, PAGE_READWRITE, &oldProtect))) {
    return;
  }

  uint8_t *p = (uint8_t *)base;
  for (SIZE_T i = 0; i < localSize; i += 16)
    aes128_decrypt_block(p + i, p + i, decKeys);

  if (!NT_SUCCESS(MyNtProtectVirtualMemory(MyGetCurrentProcess(), &base, &localSize, oldProtect, &oldProtect))) {
  }

  MyFlushInstructionCache(MyGetCurrentProcess(), base, localSize);
}

LONG CALLBACK JITDecryptVEH(PEXCEPTION_POINTERS ExceptionInfo) {

  if (ExceptionInfo->ExceptionRecord->ExceptionCode == STATUS_ACCESS_VIOLATION) {
    exit(0);
  }

  if (ExceptionInfo->ExceptionRecord->ExceptionCode != STATUS_GUARD_PAGE_VIOLATION) {
    return EXCEPTION_CONTINUE_SEARCH;
  }

  ULONG_PTR rip = ExceptionInfo->ContextRecord->Rip;
  if (rip < (ULONG_PTR)ControlStart || rip >= (ULONG_PTR)ControlStart + ControlSize) {
    exit(0);
  }

  AcquireSpinLock();

  if (pages[2]) {
    EncryptPage(pages[2]);
  }
  pages[2] = pages[1];
  pages[1] = pages[0];
  pages[0] = AlignDown((LPVOID)ExceptionInfo->ExceptionRecord->ExceptionInformation[1]);

  DecryptPage(pages[0]);

  ReleaseSpinLock();
  return EXCEPTION_CONTINUE_EXECUTION;
}
