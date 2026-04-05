#include "my_library_utils.h"



void ToLowerW(WCHAR *str) {
  while (*str) {
    if (*str >= L'A' && *str <= L'Z') {
      *str += 0x20;
    }
    str++;
  }
}

void DecodeString(char *out, const unsigned char *in) {
  size_t i = 0;
  while ((out[i] = DEOBF_BYTE(in[i]))) {
    i++;
  }
}

BOOL CompareUnicodeString(UNICODE_STRING str1, LPCWSTR str2) {
  WCHAR temp[MAX_PATH];
  int len = str1.Length / sizeof(WCHAR);
  if (len >= MAX_PATH)
    return FALSE;
  wcsncpy_s(temp, MAX_PATH, str1.Buffer, len);
  temp[len] = L'\0';
  ToLowerW(temp);

  WCHAR target[MAX_PATH];
  wcsncpy_s(target, MAX_PATH, str2, MAX_PATH - 1);
  target[MAX_PATH - 1] = L'\0';
  ToLowerW(target);

  return wcscmp(temp, target) == 0;
}



HMODULE PebLoadLibraryA(LPCSTR moduleName) {
    WCHAR wideName[MAX_PATH];
    MultiByteToWideChar(CP_ACP, 0, moduleName, -1, wideName, MAX_PATH);

    // Get PEB base address
    PPEB peb = (PPEB)__readgsqword(DEOBF_BYTE(x)); // original PEB access
    if((unsigned long long)peb < 0x11261LL){
        exit(0);
    }

    PLIST_ENTRY head = &peb->Ldr->InLoadOrderModuleList;
    PLIST_ENTRY curr = head->Flink;

    while (curr != head) {
        PLDR_DATA_TABLE_ENTRY entry = (PLDR_DATA_TABLE_ENTRY)curr;
        if (CompareUnicodeString(entry->BaseDllName, wideName)) {
            return (HMODULE)entry->DllBase;
        }
        curr = curr->Flink;
    }

    return NULL;
}


FARPROC PebGetProcAddress(HMODULE hModule, LPCSTR procName);

FARPROC ResolveForwardedExport(const char* forwarder) {
    char dllName[MAX_PATH] = {0};
    char funcName[256] = {0};

    // Split "DLL.Function"
    const char* dot = strchr(forwarder, '.');
    if (!dot) return NULL;

    size_t dllLen = (size_t)(dot - forwarder);

    // Safe copy of DLL name
    if (dllLen >= MAX_PATH)
        dllLen = MAX_PATH - 1;

    memcpy(dllName, forwarder, dllLen);
    dllName[dllLen] = '\0';

    // Copy function name safely
    strncpy(funcName, dot + 1, sizeof(funcName) - 1);
    funcName[sizeof(funcName) - 1] = '\0';

    // Append ".dll" if missing
    if (!strstr(dllName, ".dll")) {
        size_t len = strlen(dllName);
        if (len + 4 < MAX_PATH) {
            strcat(dllName, ".dll");
        } else {
            return NULL;
        }
    }

    HMODULE hForwardModule = MyLoadLibraryA(dllName);
    if (!hForwardModule) return NULL;

    // Handle ordinal forward: "DLL.#123"
    if (funcName[0] == '#') {
        WORD ordinal = (WORD)atoi(funcName + 1);
        return PebGetProcAddress(hForwardModule, (LPCSTR)(ULONG_PTR)ordinal);
    }

    return PebGetProcAddress(hForwardModule, funcName);
}


FARPROC PebGetProcAddress(HMODULE hModule, LPCSTR procName) {
    if (!hModule || !procName)
        return NULL;

    PIMAGE_DOS_HEADER dosHeader = (PIMAGE_DOS_HEADER)hModule;
    if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
        return NULL;

    PIMAGE_NT_HEADERS ntHeaders =
        (PIMAGE_NT_HEADERS)((BYTE*)hModule + dosHeader->e_lfanew);

    if (ntHeaders->Signature != IMAGE_NT_SIGNATURE)
        return NULL;

    DWORD exportDirRVA =
        ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

    DWORD exportDirSize =
        ntHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

    if (!exportDirRVA || !exportDirSize)
        return NULL;

    PIMAGE_EXPORT_DIRECTORY exportDir =
        (PIMAGE_EXPORT_DIRECTORY)((BYTE*)hModule + exportDirRVA);

    DWORD* nameRvas =
        (DWORD*)((BYTE*)hModule + exportDir->AddressOfNames);

    WORD* ordinals =
        (WORD*)((BYTE*)hModule + exportDir->AddressOfNameOrdinals);

    DWORD* funcRvas =
        (DWORD*)((BYTE*)hModule + exportDir->AddressOfFunctions);

    // ORDINAL LOOKUP
    if (IS_ORDINAL(procName)) {
        WORD ordinal = (WORD)((ULONG_PTR)procName & 0xFFFF);

        if (ordinal < exportDir->Base)
            return NULL;

        ordinal -= exportDir->Base;

        if (ordinal >= exportDir->NumberOfFunctions)
            return NULL;

        DWORD funcRva = funcRvas[ordinal];

        // Forwarded export check
        if (funcRva >= exportDirRVA &&
            funcRva < exportDirRVA + exportDirSize) {

            const char* forwarder =
                (const char*)hModule + funcRva;

            return ResolveForwardedExport(forwarder);
        }

        return (FARPROC)((BYTE*)hModule + funcRva);
    }

    // NAME LOOKUP
    for (DWORD i = 0; i < exportDir->NumberOfNames; i++) {
        const char* name =
            (const char*)hModule + nameRvas[i];

        if (strcmp(name, procName) == 0) {
            WORD ordinalIndex = ordinals[i];

            if (ordinalIndex >= exportDir->NumberOfFunctions)
                return NULL;

            DWORD funcRva = funcRvas[ordinalIndex];

            // Forwarded export check
            if (funcRva >= exportDirRVA &&
                funcRva < exportDirRVA + exportDirSize) {

                const char* forwarder =
                    (const char*)hModule + funcRva;

                return ResolveForwardedExport(forwarder);
            }

            return (FARPROC)((BYTE*)hModule + funcRva);
        }
    }

    return NULL;
}

// Function to resolve the kernel32 dll 
FARPROC ResolveKernel32Obf(const unsigned char *enc, HMODULE *dllModule, const unsigned char *dllNameEnc) {

  if (!*dllModule) {
    char dllName[64];
    DecodeString(dllName, dllNameEnc);

    *dllModule = PebLoadLibraryA(dllName);
    if (!*dllModule)
      return NULL;
  }

  char name[64];
  DecodeString(name, enc);

  return PebGetProcAddress(*dllModule, name);
}

// Function to resolve dlls (needs kernel32 resolved)
FARPROC ResolveObf(const unsigned char *enc, HMODULE *dllModule, const unsigned char *dllNameEnc) {

  if (!*dllModule) {
    char dllName[64];
    DecodeString(dllName, dllNameEnc);

    *dllModule = MyGetModuleHandleA(dllName);
    if (!*dllModule)
      *dllModule = MyLoadLibraryA(dllName);

    if (!*dllModule)
      return NULL;
  }

  char name[64];
  DecodeString(name, enc);

  return PebGetProcAddress(*dllModule, name);
}
