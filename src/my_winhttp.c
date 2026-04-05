#include "my_winhttp.h"

static HMODULE winhttpModule = NULL;

BOOL WINAPI MyWinHttpSetOption(HINTERNET a, DWORD b, LPVOID c, DWORD d) {
  static _WinHttpSetOption fn = NULL;
  if (!fn)
    fn = (_WinHttpSetOption)ResolveObf(s_WinHttpSetOption, &winhttpModule, s_winhttp_dll);
  return fn ? fn(a, b, c, d) : FALSE;
}

BOOL WINAPI MyWinHttpCrackUrl(LPCWSTR a, DWORD b, DWORD c, LPURL_COMPONENTS d) {
  static _WinHttpCrackUrl fn = NULL;
  if (!fn)
    fn = (_WinHttpCrackUrl)ResolveObf(s_WinHttpCrackUrl, &winhttpModule, s_winhttp_dll);
  return fn ? fn(a, b, c, d) : FALSE;
}

HINTERNET WINAPI MyWinHttpOpen(LPCWSTR a, DWORD b, LPCWSTR c, LPCWSTR d, DWORD e) {
  static _WinHttpOpen fn = NULL;
  if (!fn)
    fn = (_WinHttpOpen)ResolveObf(s_WinHttpOpen, &winhttpModule, s_winhttp_dll);
  return fn ? fn(a, b, c, d, e) : NULL;
}

HINTERNET WINAPI MyWinHttpConnect(HINTERNET a, LPCWSTR b, INTERNET_PORT c, DWORD d) {
  static _WinHttpConnect fn = NULL;
  if (!fn)
    fn = (_WinHttpConnect)ResolveObf(s_WinHttpConnect, &winhttpModule, s_winhttp_dll);
  return fn ? fn(a, b, c, d) : NULL;
}

HINTERNET WINAPI MyWinHttpOpenRequest(HINTERNET a, LPCWSTR b, LPCWSTR c, LPCWSTR d, LPCWSTR e, LPCWSTR *f, DWORD g) {
  static _WinHttpOpenRequest fn = NULL;
  if (!fn)
    fn = (_WinHttpOpenRequest)ResolveObf(s_WinHttpOpenRequest, &winhttpModule, s_winhttp_dll);
  return fn ? fn(a, b, c, d, e, f, g) : NULL;
}

BOOL WINAPI MyWinHttpSendRequest(HINTERNET a, LPCWSTR b, DWORD c, LPVOID d, DWORD e, DWORD f, DWORD_PTR g) {
  static _WinHttpSendRequest fn = NULL;
  if (!fn)
    fn = (_WinHttpSendRequest)ResolveObf(s_WinHttpSendRequest, &winhttpModule, s_winhttp_dll);
  return fn ? fn(a, b, c, d, e, f, g) : FALSE;
}

BOOL WINAPI MyWinHttpReceiveResponse(HINTERNET a, LPVOID b) {
  static _WinHttpReceiveResponse fn = NULL;
  if (!fn)
    fn = (_WinHttpReceiveResponse)ResolveObf(s_WinHttpReceiveResponse, &winhttpModule, s_winhttp_dll);
  return fn ? fn(a, b) : FALSE;
}

BOOL WINAPI MyWinHttpQueryHeaders(HINTERNET a, DWORD b, LPCWSTR c, LPVOID d, LPDWORD e, LPDWORD f) {
  static _WinHttpQueryHeaders fn = NULL;
  if (!fn)
    fn = (_WinHttpQueryHeaders)ResolveObf(s_WinHttpQueryHeaders, &winhttpModule, s_winhttp_dll);
  return fn ? fn(a, b, c, d, e, f) : FALSE;
}

BOOL WINAPI MyWinHttpQueryDataAvailable(HINTERNET a, LPDWORD b) {
  static _WinHttpQueryDataAvailable fn = NULL;
  if (!fn)
    fn = (_WinHttpQueryDataAvailable)ResolveObf(s_WinHttpQueryDataAvailable, &winhttpModule, s_winhttp_dll);
  return fn ? fn(a, b) : FALSE;
}

BOOL WINAPI MyWinHttpReadData(HINTERNET a, LPVOID b, DWORD c, LPDWORD d) {
  static _WinHttpReadData fn = NULL;
  if (!fn)
    fn = (_WinHttpReadData)ResolveObf(s_WinHttpReadData, &winhttpModule, s_winhttp_dll);
  return fn ? fn(a, b, c, d) : FALSE;
}

BOOL WINAPI MyWinHttpCloseHandle(HINTERNET a) {
  static _WinHttpCloseHandle fn = NULL;
  if (!fn)
    fn = (_WinHttpCloseHandle)ResolveObf(s_WinHttpCloseHandle, &winhttpModule, s_winhttp_dll);
  return fn ? fn(a) : FALSE;
}