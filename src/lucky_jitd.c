#include "lucky_jitd.h"

volatile LONG vehLock = 0;

static LPVOID pagePrevPrev = NULL;
static LPVOID pagePrev = NULL;
static LPVOID pageCurr = NULL;

int vehInstalled = 0;
SIZE_T pageSize = 0;

LPVOID ControlStart = 0;
SIZE_T ControlSize = 0;

void AcquireSpinLock() {
  while (InterlockedCompareExchange(&vehLock, 1, 0) != 0)
    YieldProcessor();
}

void ProtectMemoryPages(LPVOID start, SIZE_T size) {
  ControlStart = start;
  ControlSize = size;

  ULONG oldProtect;
  SYSTEM_INFO si;

  MyGetSystemInfo(&si);

  SIZE_T pageSize = si.dwPageSize;

  for (SIZE_T offset = 0; offset < size; offset += pageSize) {
    PVOID page = (PBYTE)start + offset;
    SIZE_T regionSize = pageSize;

    NTSTATUS status = MyNtProtectVirtualMemory(MyGetCurrentProcess(), &page, &regionSize, PAGE_EXECUTE_READ | PAGE_GUARD, &oldProtect);

    if (status < 0) {

      break;
    }
  }
}

void ReleaseSpinLock() { InterlockedExchange(&vehLock, 0); }

void EncryptPage(void *page) {

  ULONG oldProtect;
  SIZE_T localSize = pageSize;
  PVOID base = page;

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
  SIZE_T localSize = pageSize;
  PVOID base = page;

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

  if (pageSize == 0) {
    SYSTEM_INFO si;
    MyGetSystemInfo(&si);
    pageSize = si.dwPageSize;
  }

  ULONG_PTR rip = ExceptionInfo->ContextRecord->Rip;
  if (rip < (ULONG_PTR)ControlStart || rip >= (ULONG_PTR)ControlStart + ControlSize) {
    exit(0);
  }

  AcquireSpinLock();

  LPVOID faultAddr = (LPVOID)ExceptionInfo->ExceptionRecord->ExceptionInformation[1];

  LPVOID newPage = (LPVOID)((ULONG_PTR)faultAddr & ~(pageSize - 1));

  DecryptPage(newPage);

  if (pagePrevPrev) {
    EncryptPage(pagePrevPrev);
  }

  pagePrevPrev = pagePrev;
  pagePrev = pageCurr;
  pageCurr = newPage;

  ReleaseSpinLock();
  return EXCEPTION_CONTINUE_EXECUTION;
}