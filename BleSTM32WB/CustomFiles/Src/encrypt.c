/*
 * 	encrypt.c
 *
 *  Created on: Feb 25, 2025
 *      Author: pepiv
 */
#include  "encrypt.h"

static uint8_t scratch[SCRATCH_SIZE];
static uint8_t ecc_ctx_buf[ECC_CTX_SIZE];

uint8_t ecdh_private[PRIVKEY_SIZE];
uint8_t ecdh_public[PUBKEY_SIZE];
uint8_t shared_secret[SECRET_SIZE];
uint8_t aes_key[32];

extern volatile uint32_t uwTick;

static uint8_t scratch[SCRATCH_SIZE];
static unsigned char key[32] = {
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
		0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
		0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20
};

uint8_t nonce[12] = {
	    0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x07, 0x18,
	    0x29, 0x3A, 0x4B, 0x5C
};

uint32_t get_micros()
{
	uint32_t ms_ticks, systick_val, systick_reload;
	do {
		ms_ticks = uwTick;
		systick_val = SysTick->VAL;
		systick_reload = SysTick->LOAD;
	} while (ms_ticks != uwTick);


	uint32_t uptime_us = (ms_ticks * 1000) + ((systick_reload - systick_val) / (HAL_RCC_GetHCLKFreq() / 1000000));

	return uptime_us;
	return 0;
}

int chacha_encrypt_and_tag(const unsigned char *in, size_t in_len, const unsigned char *aad, size_t aad_len, unsigned char *out, unsigned char tag[16]) {
	mbedtls_chachapoly_context ctx;
	mbedtls_chachapoly_init(&ctx);
	mbedtls_chachapoly_setkey(&ctx, key);
	int returnable = mbedtls_chachapoly_encrypt_and_tag(&ctx, in_len, nonce, aad, aad_len, in, out, tag);
	mbedtls_chacha20_free(&ctx);
	return returnable;
}

int chacha20_encrypt(const uint8_t *in, size_t len, uint32_t counter, uint8_t *out)
{
    return mbedtls_chacha20_crypt(key, nonce, counter, len, in, out);
}

void cmox_init_once(void) {
    static bool initialized = false;
    if (!initialized) {
        cmox_initialize(NULL);
        initialized = true;
    }
}

int aes_gcm_encrypt_and_tag(const uint8_t *in, size_t in_len,
                            const uint8_t *aad, size_t aad_len,
                            uint8_t *out_with_tag)
{

    cmox_cipher_retval_t result;

    cmox_init_once();

    result = cmox_aead_encrypt(
        CMOX_AESFAST_GCMFAST_ENC_ALGO,
        in, in_len,
        TAG_SIZE,
        key, sizeof(key),
        nonce, sizeof(nonce),
        aad, aad_len,
        out_with_tag, in_len + TAG_SIZE);

    return (result == CMOX_CIPHER_SUCCESS) ? 0 : -1;
}

