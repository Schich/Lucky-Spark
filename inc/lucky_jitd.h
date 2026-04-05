#include "lucky_cipher.h"
#include "lucky_fiber_loader.h"
#include "my_kernel32.h"
#include "my_ntdll.h"
#include <immintrin.h>
#include <intrin.h>
#include <stddef.h>
#include <stdint.h>
#include <windows.h>
#include <winnt.h>

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

void ProtectMemoryPages(LPVOID start, SIZE_T size);
LONG CALLBACK JITDecryptVEH(PEXCEPTION_POINTERS ExceptionInfo);