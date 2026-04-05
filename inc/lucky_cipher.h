#pragma once


#include "my_kernel32.h"
#include "my_ntdll.h"
#include <stdint.h>
#include <string.h>
#include <windows.h>

#include <stdint.h>
//TODO: remove stdio
#include <stdio.h>
#include <string.h>
#include "my_library_utils.h"

#define ROUND_KEYS_SIZE 176

typedef uint8_t round_keys_t[ROUND_KEYS_SIZE] __attribute__((aligned(16)));
extern round_keys_t encKeys;
extern round_keys_t decKeys;


void initLuckyCipher();
void aes128_encrypt_block(uint8_t *in, uint8_t *out, round_keys_t roundKeys);
void aes128_decrypt_block(uint8_t *in, uint8_t *out, round_keys_t roundKeys);
