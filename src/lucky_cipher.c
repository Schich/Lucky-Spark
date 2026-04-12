#include "../inc/lucky_cipher.h"
#include <stdint.h>
#define getSBoxValue(num) (sbox[(num)])

#define Nk 4
#define Nb 4
#define Nr 10

#define PAGE_SECTION __attribute__((section(".lucky_page"), noinline, used))

round_keys_t encKeys;
round_keys_t decKeys;

extern uint8_t patch_target[];

static uint8_t Rcon[11] = {OBF_BYTE(0x8d), OBF_BYTE(0x01), OBF_BYTE(0x02), OBF_BYTE(0x04), OBF_BYTE(0x08), OBF_BYTE(0x10), OBF_BYTE(0x20), OBF_BYTE(0x40), OBF_BYTE(0x80), OBF_BYTE(0x1b), OBF_BYTE(0x36)};

static uint8_t sbox[256] = {OBF_BYTE(0x63), OBF_BYTE(0x7c), OBF_BYTE(0x77), OBF_BYTE(0x7b), OBF_BYTE(0xf2), OBF_BYTE(0x6b), OBF_BYTE(0x6f), OBF_BYTE(0xc5), OBF_BYTE(0x30), OBF_BYTE(0x01), OBF_BYTE(0x67), OBF_BYTE(0x2b), OBF_BYTE(0xfe), OBF_BYTE(0xd7), OBF_BYTE(0xab), OBF_BYTE(0x76), OBF_BYTE(0xca), OBF_BYTE(0x82), OBF_BYTE(0xc9), OBF_BYTE(0x7d), OBF_BYTE(0xfa), OBF_BYTE(0x59), OBF_BYTE(0x47), OBF_BYTE(0xf0), OBF_BYTE(0xad), OBF_BYTE(0xd4), OBF_BYTE(0xa2), OBF_BYTE(0xaf), OBF_BYTE(0x9c), OBF_BYTE(0xa4), OBF_BYTE(0x72), OBF_BYTE(0xc0), OBF_BYTE(0xb7), OBF_BYTE(0xfd), OBF_BYTE(0x93), OBF_BYTE(0x26), OBF_BYTE(0x36), OBF_BYTE(0x3f), OBF_BYTE(0xf7), OBF_BYTE(0xcc), OBF_BYTE(0x34), OBF_BYTE(0xa5), OBF_BYTE(0xe5), OBF_BYTE(0xf1), OBF_BYTE(0x71), OBF_BYTE(0xd8), OBF_BYTE(0x31), OBF_BYTE(0x15), OBF_BYTE(0x04), OBF_BYTE(0xc7), OBF_BYTE(0x23), OBF_BYTE(0xc3),
                            OBF_BYTE(0x18), OBF_BYTE(0x96), OBF_BYTE(0x05), OBF_BYTE(0x9a), OBF_BYTE(0x07), OBF_BYTE(0x12), OBF_BYTE(0x80), OBF_BYTE(0xe2), OBF_BYTE(0xeb), OBF_BYTE(0x27), OBF_BYTE(0xb2), OBF_BYTE(0x75), OBF_BYTE(0x09), OBF_BYTE(0x83), OBF_BYTE(0x2c), OBF_BYTE(0x1a), OBF_BYTE(0x1b), OBF_BYTE(0x6e), OBF_BYTE(0x5a), OBF_BYTE(0xa0), OBF_BYTE(0x52), OBF_BYTE(0x3b), OBF_BYTE(0xd6), OBF_BYTE(0xb3), OBF_BYTE(0x29), OBF_BYTE(0xe3), OBF_BYTE(0x2f), OBF_BYTE(0x84), OBF_BYTE(0x53), OBF_BYTE(0xd1), OBF_BYTE(0x00), OBF_BYTE(0xed), OBF_BYTE(0x20), OBF_BYTE(0xfc), OBF_BYTE(0xb1), OBF_BYTE(0x5b), OBF_BYTE(0x6a), OBF_BYTE(0xcb), OBF_BYTE(0xbe), OBF_BYTE(0x39), OBF_BYTE(0x4a), OBF_BYTE(0x4c), OBF_BYTE(0x58), OBF_BYTE(0xcf), OBF_BYTE(0xd0), OBF_BYTE(0xef), OBF_BYTE(0xaa), OBF_BYTE(0xfb), OBF_BYTE(0x43), OBF_BYTE(0x4d), OBF_BYTE(0x33), OBF_BYTE(0x85),
                            OBF_BYTE(0x45), OBF_BYTE(0xf9), OBF_BYTE(0x02), OBF_BYTE(0x7f), OBF_BYTE(0x50), OBF_BYTE(0x3c), OBF_BYTE(0x9f), OBF_BYTE(0xa8), OBF_BYTE(0x51), OBF_BYTE(0xa3), OBF_BYTE(0x40), OBF_BYTE(0x8f), OBF_BYTE(0x92), OBF_BYTE(0x9d), OBF_BYTE(0x38), OBF_BYTE(0xf5), OBF_BYTE(0xbc), OBF_BYTE(0xb6), OBF_BYTE(0xda), OBF_BYTE(0x21), OBF_BYTE(0x10), OBF_BYTE(0xff), OBF_BYTE(0xf3), OBF_BYTE(0xd2), OBF_BYTE(0xcd), OBF_BYTE(0x0c), OBF_BYTE(0x13), OBF_BYTE(0xec), OBF_BYTE(0x5f), OBF_BYTE(0x97), OBF_BYTE(0x44), OBF_BYTE(0x17), OBF_BYTE(0xc4), OBF_BYTE(0xa7), OBF_BYTE(0x7e), OBF_BYTE(0x3d), OBF_BYTE(0x64), OBF_BYTE(0x5d), OBF_BYTE(0x19), OBF_BYTE(0x73), OBF_BYTE(0x60), OBF_BYTE(0x81), OBF_BYTE(0x4f), OBF_BYTE(0xdc), OBF_BYTE(0x22), OBF_BYTE(0x2a), OBF_BYTE(0x90), OBF_BYTE(0x88), OBF_BYTE(0x46), OBF_BYTE(0xee), OBF_BYTE(0xb8), OBF_BYTE(0x14),
                            OBF_BYTE(0xde), OBF_BYTE(0x5e), OBF_BYTE(0x0b), OBF_BYTE(0xdb), OBF_BYTE(0xe0), OBF_BYTE(0x32), OBF_BYTE(0x3a), OBF_BYTE(0x0a), OBF_BYTE(0x49), OBF_BYTE(0x06), OBF_BYTE(0x24), OBF_BYTE(0x5c), OBF_BYTE(0xc2), OBF_BYTE(0xd3), OBF_BYTE(0xac), OBF_BYTE(0x62), OBF_BYTE(0x91), OBF_BYTE(0x95), OBF_BYTE(0xe4), OBF_BYTE(0x79), OBF_BYTE(0xe7), OBF_BYTE(0xc8), OBF_BYTE(0x37), OBF_BYTE(0x6d), OBF_BYTE(0x8d), OBF_BYTE(0xd5), OBF_BYTE(0x4e), OBF_BYTE(0xa9), OBF_BYTE(0x6c), OBF_BYTE(0x56), OBF_BYTE(0xf4), OBF_BYTE(0xea), OBF_BYTE(0x65), OBF_BYTE(0x7a), OBF_BYTE(0xae), OBF_BYTE(0x08), OBF_BYTE(0xba), OBF_BYTE(0x78), OBF_BYTE(0x25), OBF_BYTE(0x2e), OBF_BYTE(0x1c), OBF_BYTE(0xa6), OBF_BYTE(0xb4), OBF_BYTE(0xc6), OBF_BYTE(0xe8), OBF_BYTE(0xdd), OBF_BYTE(0x74), OBF_BYTE(0x1f), OBF_BYTE(0x4b), OBF_BYTE(0xbd), OBF_BYTE(0x8b), OBF_BYTE(0x8a),
                            OBF_BYTE(0x70), OBF_BYTE(0x3e), OBF_BYTE(0xb5), OBF_BYTE(0x66), OBF_BYTE(0x48), OBF_BYTE(0x03), OBF_BYTE(0xf6), OBF_BYTE(0x0e), OBF_BYTE(0x61), OBF_BYTE(0x35), OBF_BYTE(0x57), OBF_BYTE(0xb9), OBF_BYTE(0x86), OBF_BYTE(0xc1), OBF_BYTE(0x1d), OBF_BYTE(0x9e), OBF_BYTE(0xe1), OBF_BYTE(0xf8), OBF_BYTE(0x98), OBF_BYTE(0x11), OBF_BYTE(0x69), OBF_BYTE(0xd9), OBF_BYTE(0x8e), OBF_BYTE(0x94), OBF_BYTE(0x9b), OBF_BYTE(0x1e), OBF_BYTE(0x87), OBF_BYTE(0xe9), OBF_BYTE(0xce), OBF_BYTE(0x55), OBF_BYTE(0x28), OBF_BYTE(0xdf), OBF_BYTE(0x8c), OBF_BYTE(0xa1), OBF_BYTE(0x89), OBF_BYTE(0x0d), OBF_BYTE(0xbf), OBF_BYTE(0xe6), OBF_BYTE(0x42), OBF_BYTE(0x68), OBF_BYTE(0x41), OBF_BYTE(0x99), OBF_BYTE(0x2d), OBF_BYTE(0x0f), OBF_BYTE(0xb0), OBF_BYTE(0x54), OBF_BYTE(0xbb), OBF_BYTE(0x16)};

static void KeyExpansion(round_keys_t RoundKey, uint8_t *Key) {
  uint8_t tempa[4];
  unsigned i, k;

  for (i = 0; i < Nk * 4; ++i)
    RoundKey[i] = Key[i];

  for (i = Nk; i < Nb * (Nr + 1); ++i) {

    for (k = 0; k < 4; ++k)
      tempa[k] = RoundKey[4 * (i - 1) + k];

    if (i % Nk == 0) {

      uint8_t t = tempa[0];
      tempa[0] = tempa[1];
      tempa[1] = tempa[2];
      tempa[2] = tempa[3];
      tempa[3] = t;

      for (k = 0; k < 4; ++k)
        tempa[k] = getSBoxValue(tempa[k]);

      tempa[0] ^= Rcon[i / Nk];
    }

    for (k = 0; k < 4; ++k)
      RoundKey[4 * i + k] = RoundKey[4 * (i - Nk) + k] ^ tempa[k];
  }
}


PAGE_SECTION void section_start(){};

PAGE_SECTION void GenerateDecryptionKeys(uint8_t *encKeys, round_keys_t decKeys) {
  __asm__ volatile(".intel_syntax noprefix \n"

                   "mov rsi, %[enc] \n"
                   "mov rdi, %[dec] \n"
                   "add rsi, 160 \n"
                   "mov rcx, 16 \n"
                   "rep movsb \n"
                   "mov ecx, 1 \n"
                   "1: \n"
                   "mov rsi, %[enc] \n"
                   "mov rdi, %[dec] \n"
                   "mov rax, rcx \n"
                   "imul rax, 16 \n"
                   "mov rbx, 160 \n"
                   "sub rax, rbx \n"
                   "neg rax \n"
                   "add rsi, rax \n"
                   "movdqu xmm0, [rsi] \n"
                   "patch_target:\n"
                   "pmuldq xmm0, xmm0 \n" // replaced pmuldq with aesimc here
                   "mov rdi, %[dec] \n"
                   "mov rax, rcx \n"
                   "imul rax, 16 \n"
                   "add rdi, rax \n"
                   "movdqu [rdi], xmm0 \n"
                   "inc ecx \n"
                   "cmp ecx, 10 \n"
                   "jl 1b \n"
                   "mov rsi, %[enc] \n"
                   "mov rdi, %[dec] \n"
                   "add rdi, 160 \n"
                   "mov rcx, 16 \n"
                   "rep movsb \n"
                   ".att_syntax prefix \n"
                   :
                   : [enc] "r"(encKeys), [dec] "r"(decKeys)
                   : "rax", "rbx", "rcx", "rsi", "rdi", "xmm0", "memory");
}
PAGE_SECTION void GenerateDecryptionKeys_end() {}

PAGE_SECTION void aes128_encrypt_block(uint8_t *in, uint8_t *out, round_keys_t roundKeys) {
  __asm__ volatile("movdqu (%0), %%xmm0      \n\t"
                   "movdqu (%1), %%xmm1      \n\t"
                   "pxor %%xmm1, %%xmm0      \n\t"
                   "movdqu 16(%1), %%xmm1    \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 32(%1), %%xmm1    \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 48(%1), %%xmm1    \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 64(%1), %%xmm1    \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 80(%1), %%xmm1    \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 96(%1), %%xmm1    \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 112(%1), %%xmm1   \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 128(%1), %%xmm1   \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 144(%1), %%xmm1   \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 160(%1), %%xmm1   \n\t"
                   "pcmpeqq %%xmm1, %%xmm0 \n\t"
                   "movdqu %%xmm0, (%2)      \n\t"
                   "pxor %%xmm0, %%xmm0      \n\t"
                   "pxor %%xmm1, %%xmm1      \n\t"
                   :
                   : "r"(in), "r"(roundKeys), "r"(out)
                   : "xmm0", "xmm1", "memory");
}
PAGE_SECTION void aes128_encrypt_block_end() {}

PAGE_SECTION void aes128_decrypt_block(uint8_t *in, uint8_t *out, round_keys_t decKeys) {
  __asm__ volatile("movdqu (%0), %%xmm0      \n\t"
                   "movdqu (%1), %%xmm1      \n\t"
                   "pxor %%xmm1, %%xmm0      \n\t"
                   "movdqu 16(%1), %%xmm1    \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 32(%1), %%xmm1    \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 48(%1), %%xmm1    \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 64(%1), %%xmm1    \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 80(%1), %%xmm1    \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 96(%1), %%xmm1    \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 112(%1), %%xmm1   \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 128(%1), %%xmm1   \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 144(%1), %%xmm1   \n\t"
                   "pmuldq %%xmm1, %%xmm0    \n\t"
                   "movdqu 160(%1), %%xmm1   \n\t"
                   "pcmpeqq %%xmm1, %%xmm0\n\t"
                   "movdqu %%xmm0, (%2)      \n\t"
                   "pxor %%xmm0, %%xmm0      \n\t"
                   "pxor %%xmm1, %%xmm1      \n\t"
                   :
                   : "r"(in), "r"(decKeys), "r"(out)
                   : "xmm0", "xmm1", "memory");
}
PAGE_SECTION void aes128_decrypt_block_end() {}

PAGE_SECTION void section_end(){};


 void randomKey(uint8_t key[16]) {
  uint64_t *k64 = (uint64_t *)key;

  for (int i = 0; i < 2; i++) {
    unsigned char ok;
    uint64_t val;

    do {
      __asm__ volatile("rdseed %0\n\t"
                       "setc %1"
                       : "=r"(val), "=qm"(ok)
                       :
                       :);
    } while (!ok);

    k64[i] = val;
  }
}

void secureZero(void *v, size_t n) {
  volatile uint8_t *p = (volatile uint8_t *)v;
  while (n--)
    *p++ = 0;
}

 void patch_bytes(uint8_t *start, size_t size, const uint8_t x[5], const uint8_t y[5]) {

  for (size_t i = 0; i + 5 <= size; ++i) {
    if (memcmp(start + i, x, 5) == 0) {
      memcpy(start + i, y, 5);
      i += 4;
    }
  }

  MyFlushInstructionCache(MyGetCurrentProcess(), start, size);
}

void initLuckyCipher() {
  const uint8_t pmuldq[5] = {0x66, 0x0F, 0x38, 0x28, 0xC1};
  const uint8_t pcmpeqq[5] = {0x66, 0x0F, 0x38, 0x29, 0xC1};
  const uint8_t aesenc[5] = {0x66, 0x0F, 0x38, 0xDC, 0xC1};
  const uint8_t aesenclast[5] = {0x66, 0x0F, 0x38, 0xDD, 0xC1};
  const uint8_t aesdec[5] = {0x66, 0x0F, 0x38, 0xDE, 0xC1};
  const uint8_t aesdeclast[5] = {0x66, 0x0F, 0x38, 0xDF, 0xC1};
  const uint8_t aesimc[5] = {0x66, 0x0F, 0x38, 0xDB, 0xC0};
  const uint8_t pmuldq2[5] = {0x66, 0x0F, 0x38, 0x28, 0xC0};


uint8_t *secStart = (uint8_t *)section_start;
uint8_t *secEnd   = (uint8_t *)section_end;
DWORD oldProtect;
PVOID base = (PVOID)((ULONG_PTR)secStart & ~0xFFF);
SIZE_T secSze = (SIZE_T)(secEnd - (uint8_t *)base + 0xFFF) & ~0xFFF;

MyNtProtectVirtualMemory(
    MyGetCurrentProcess(),
    &base,
    &secSze,
    PAGE_READWRITE,
    &oldProtect
);

  uint8_t *start = (uint8_t *)aes128_decrypt_block;
  uint8_t *end = (uint8_t *)aes128_decrypt_block_end;
  size_t size = end - start;

  patch_bytes(start, size, pmuldq, aesdec);
  patch_bytes(start, size, pcmpeqq, aesdeclast);

  start = (uint8_t *)aes128_encrypt_block;
  end = (uint8_t *)aes128_encrypt_block_end;
  size = end - start;
  patch_bytes(start, size, pmuldq, aesenc);
  patch_bytes(start, size, pcmpeqq, aesenclast);

  start = (uint8_t *)GenerateDecryptionKeys;
  end = (uint8_t *)GenerateDecryptionKeys_end;
  size = end - start;
  patch_bytes(start, size, pmuldq2, aesimc);

  MyNtProtectVirtualMemory(MyGetCurrentProcess(), &base, &secSze, oldProtect, &oldProtect);

  uint8_t key[16];
  randomKey(key);
  KeyExpansion(encKeys, key);
  GenerateDecryptionKeys(encKeys, decKeys);
  secureZero(key, sizeof(key));
}
