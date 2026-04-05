

#pragma once
#include "my_library_utils.h" 
#include <windows.h>
#include <winhttp.h>

typedef BOOL(WINAPI *_WinHttpCrackUrl)(LPCWSTR, DWORD, DWORD, LPURL_COMPONENTS);
typedef HINTERNET(WINAPI *_WinHttpOpen)(LPCWSTR, DWORD, LPCWSTR, LPCWSTR, DWORD);
typedef HINTERNET(WINAPI *_WinHttpConnect)(HINTERNET, LPCWSTR, INTERNET_PORT, DWORD);
typedef HINTERNET(WINAPI *_WinHttpOpenRequest)(HINTERNET, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR *, DWORD);
typedef BOOL(WINAPI *_WinHttpSendRequest)(HINTERNET, LPCWSTR, DWORD, LPVOID, DWORD, DWORD, DWORD_PTR);
typedef BOOL(WINAPI *_WinHttpReceiveResponse)(HINTERNET, LPVOID);
typedef BOOL(WINAPI *_WinHttpQueryHeaders)(HINTERNET, DWORD, LPCWSTR, LPVOID, LPDWORD, LPDWORD);
typedef BOOL(WINAPI *_WinHttpQueryDataAvailable)(HINTERNET, LPDWORD);
typedef BOOL(WINAPI *_WinHttpReadData)(HINTERNET, LPVOID, DWORD, LPDWORD);
typedef BOOL(WINAPI *_WinHttpCloseHandle)(HINTERNET);
typedef BOOL(WINAPI *_WinHttpSetOption)(HINTERNET, DWORD, LPVOID, DWORD);

BOOL WINAPI MyWinHttpCrackUrl(LPCWSTR a, DWORD b, DWORD c, LPURL_COMPONENTS d);
HINTERNET WINAPI MyWinHttpOpen(LPCWSTR a, DWORD b, LPCWSTR c, LPCWSTR d, DWORD e);
HINTERNET WINAPI MyWinHttpConnect(HINTERNET a, LPCWSTR b, INTERNET_PORT c, DWORD d);
HINTERNET WINAPI MyWinHttpOpenRequest(HINTERNET a, LPCWSTR b, LPCWSTR c, LPCWSTR d, LPCWSTR e, LPCWSTR *f, DWORD g);
BOOL WINAPI MyWinHttpSendRequest(HINTERNET a, LPCWSTR b, DWORD c, LPVOID d, DWORD e, DWORD f, DWORD_PTR g);
BOOL WINAPI MyWinHttpReceiveResponse(HINTERNET a, LPVOID b);
BOOL WINAPI MyWinHttpQueryHeaders(HINTERNET a, DWORD b, LPCWSTR c, LPVOID d, LPDWORD e, LPDWORD f);
BOOL WINAPI MyWinHttpQueryDataAvailable(HINTERNET a, LPDWORD b);
BOOL WINAPI MyWinHttpReadData(HINTERNET a, LPVOID b, DWORD c, LPDWORD d);
BOOL WINAPI MyWinHttpCloseHandle(HINTERNET a);
BOOL WINAPI MyWinHttpSetOption(HINTERNET a, DWORD b, LPVOID c, DWORD d);

// Obfuscated API names
static const unsigned char s_WinHttpCrackUrl[] = {OBF_BYTE('W'), OBF_BYTE('i'), OBF_BYTE('n'), OBF_BYTE('H'), OBF_BYTE('t'), OBF_BYTE('t'), OBF_BYTE('p'), OBF_BYTE('C'), OBF_BYTE('r'), OBF_BYTE('a'), OBF_BYTE('c'), OBF_BYTE('k'), OBF_BYTE('U'), OBF_BYTE('r'), OBF_BYTE('l'), OBF_BYTE(0x00)};
static const unsigned char s_WinHttpOpen[] = {OBF_BYTE('W'), OBF_BYTE('i'), OBF_BYTE('n'), OBF_BYTE('H'), OBF_BYTE('t'), OBF_BYTE('t'), OBF_BYTE('p'), OBF_BYTE('O'), OBF_BYTE('p'), OBF_BYTE('e'), OBF_BYTE('n'), OBF_BYTE(0x00)};
static const unsigned char s_WinHttpConnect[] = {OBF_BYTE('W'), OBF_BYTE('i'), OBF_BYTE('n'), OBF_BYTE('H'), OBF_BYTE('t'), OBF_BYTE('t'), OBF_BYTE('p'), OBF_BYTE('C'), OBF_BYTE('o'), OBF_BYTE('n'), OBF_BYTE('n'), OBF_BYTE('e'), OBF_BYTE('c'), OBF_BYTE('t'), OBF_BYTE(0x00)};
static const unsigned char s_WinHttpOpenRequest[] = {OBF_BYTE('W'), OBF_BYTE('i'), OBF_BYTE('n'), OBF_BYTE('H'), OBF_BYTE('t'), OBF_BYTE('t'), OBF_BYTE('p'), OBF_BYTE('O'), OBF_BYTE('p'), OBF_BYTE('e'), OBF_BYTE('n'), OBF_BYTE('R'), OBF_BYTE('e'), OBF_BYTE('q'), OBF_BYTE('u'), OBF_BYTE('e'), OBF_BYTE('s'), OBF_BYTE('t'), OBF_BYTE(0x00)};
static const unsigned char s_WinHttpSendRequest[] = {OBF_BYTE('W'), OBF_BYTE('i'), OBF_BYTE('n'), OBF_BYTE('H'), OBF_BYTE('t'), OBF_BYTE('t'), OBF_BYTE('p'), OBF_BYTE('S'), OBF_BYTE('e'), OBF_BYTE('n'), OBF_BYTE('d'), OBF_BYTE('R'), OBF_BYTE('e'), OBF_BYTE('q'), OBF_BYTE('u'), OBF_BYTE('e'), OBF_BYTE('s'), OBF_BYTE('t'), OBF_BYTE(0x00)};
static const unsigned char s_WinHttpReceiveResponse[] = {OBF_BYTE('W'), OBF_BYTE('i'), OBF_BYTE('n'), OBF_BYTE('H'), OBF_BYTE('t'), OBF_BYTE('t'), OBF_BYTE('p'), OBF_BYTE('R'), OBF_BYTE('e'), OBF_BYTE('c'), OBF_BYTE('e'), OBF_BYTE('i'), OBF_BYTE('v'), OBF_BYTE('e'), OBF_BYTE('R'), OBF_BYTE('e'), OBF_BYTE('s'), OBF_BYTE('p'), OBF_BYTE('o'), OBF_BYTE('n'), OBF_BYTE('s'), OBF_BYTE('e'), OBF_BYTE(0x00)};
static const unsigned char s_WinHttpQueryHeaders[] = {OBF_BYTE('W'), OBF_BYTE('i'), OBF_BYTE('n'), OBF_BYTE('H'), OBF_BYTE('t'), OBF_BYTE('t'), OBF_BYTE('p'), OBF_BYTE('Q'), OBF_BYTE('u'), OBF_BYTE('e'), OBF_BYTE('r'), OBF_BYTE('y'), OBF_BYTE('H'), OBF_BYTE('e'), OBF_BYTE('a'), OBF_BYTE('d'), OBF_BYTE('e'), OBF_BYTE('r'), OBF_BYTE('s'), OBF_BYTE(0x00)};
static const unsigned char s_WinHttpQueryDataAvailable[] = {OBF_BYTE('W'), OBF_BYTE('i'), OBF_BYTE('n'), OBF_BYTE('H'), OBF_BYTE('t'), OBF_BYTE('t'), OBF_BYTE('p'), OBF_BYTE('Q'), OBF_BYTE('u'), OBF_BYTE('e'), OBF_BYTE('r'), OBF_BYTE('y'), OBF_BYTE('D'), OBF_BYTE('a'), OBF_BYTE('t'), OBF_BYTE('a'), OBF_BYTE('A'), OBF_BYTE('v'), OBF_BYTE('a'), OBF_BYTE('i'), OBF_BYTE('l'), OBF_BYTE('a'), OBF_BYTE('b'), OBF_BYTE('l'), OBF_BYTE('e'), OBF_BYTE(0x00)};
static const unsigned char s_WinHttpReadData[] = {OBF_BYTE('W'), OBF_BYTE('i'), OBF_BYTE('n'), OBF_BYTE('H'), OBF_BYTE('t'), OBF_BYTE('t'), OBF_BYTE('p'), OBF_BYTE('R'), OBF_BYTE('e'), OBF_BYTE('a'), OBF_BYTE('d'), OBF_BYTE('D'), OBF_BYTE('a'), OBF_BYTE('t'), OBF_BYTE('a'), OBF_BYTE(0x00)};
static const unsigned char s_WinHttpCloseHandle[] = {OBF_BYTE('W'), OBF_BYTE('i'), OBF_BYTE('n'), OBF_BYTE('H'), OBF_BYTE('t'), OBF_BYTE('t'), OBF_BYTE('p'), OBF_BYTE('C'), OBF_BYTE('l'), OBF_BYTE('o'), OBF_BYTE('s'), OBF_BYTE('e'), OBF_BYTE('H'), OBF_BYTE('a'), OBF_BYTE('n'), OBF_BYTE('d'), OBF_BYTE('l'), OBF_BYTE('e'), OBF_BYTE(0x00)};
static const unsigned char s_WinHttpSetOption[] = {OBF_BYTE('W'), OBF_BYTE('i'), OBF_BYTE('n'), OBF_BYTE('H'), OBF_BYTE('t'), OBF_BYTE('t'), OBF_BYTE('p'), OBF_BYTE('S'), OBF_BYTE('e'), OBF_BYTE('t'), OBF_BYTE('O'), OBF_BYTE('p'), OBF_BYTE('t'), OBF_BYTE('i'), OBF_BYTE('o'), OBF_BYTE('n'), OBF_BYTE(0x00)};
static const unsigned char s_winhttp_dll[] = {OBF_BYTE('w'), OBF_BYTE('i'), OBF_BYTE('n'), OBF_BYTE('h'), OBF_BYTE('t'), OBF_BYTE('t'), OBF_BYTE('p'), OBF_BYTE('.'), OBF_BYTE('d'), OBF_BYTE('l'), OBF_BYTE('l'), OBF_BYTE(0x00)};

