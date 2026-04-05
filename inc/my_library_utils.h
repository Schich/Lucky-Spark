#pragma once
#include <windows.h>
#include "lucky_obf_configs.h"


#ifndef OBF_BYTE
#define OBF_BYTE(x) ((unsigned char)((A * (x) + B) & 0xFF))
#endif 

#ifndef DEOBF_BYTE
#define DEOBF_BYTE(x) ((unsigned char)((INV_A * ((x) - B)) & 0xFF))
#endif


#define IS_ORDINAL(x) (((ULONG_PTR)(x) >> 16) == 0)

// UNICODE / PEB Structures
typedef struct _UNICODE_STRING {
  USHORT Length;
  USHORT MaximumLength;
  PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _LDR_DATA_TABLE_ENTRY {
  LIST_ENTRY InLoadOrderLinks;
  LIST_ENTRY InMemoryOrderLinks;
  LIST_ENTRY InInitializationOrderLinks;
  PVOID DllBase;
  PVOID EntryPoint;
  ULONG SizeOfImage;
  UNICODE_STRING FullDllName;
  UNICODE_STRING BaseDllName;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _PEB_LDR_DATA {
  ULONG Length;
  BOOLEAN Initialized;
  PVOID SsHandle;
  LIST_ENTRY InLoadOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef struct _PEB {
  BYTE Reserved1[2];
  BYTE BeingDebugged;
  BYTE Reserved2[1];
  PVOID Reserved3[2];
  PPEB_LDR_DATA Ldr;
} PEB, *PPEB;

HMODULE WINAPI MyGetModuleHandleA(LPCSTR lpModuleName);

PPEB GetPEB();

void ToLowerW(WCHAR *str);

BOOL CompareUnicodeString(UNICODE_STRING str1, LPCWSTR str2);

HMODULE PebLoadLibraryA(LPCSTR moduleName);
HMODULE WINAPI MyLoadLibraryA(LPCSTR lpLibFileName);

FARPROC ResolveKernel32Obf(const unsigned char *enc, HMODULE *dllModule, const unsigned char *dllNameEnc);

FARPROC ResolveObf(const unsigned char *enc, HMODULE *dllModule, const unsigned char *dllNameEnc);

void DecodeString(char *out, const unsigned char *in);

static const unsigned char x = OBF_BYTE(0x60);
