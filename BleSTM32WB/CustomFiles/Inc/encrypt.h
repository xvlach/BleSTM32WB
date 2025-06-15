/*
 * 	encrypt.h
 *
 *  Created on: Feb 25, 2025
 *      Author: pepiv
 */

#ifndef INC_ENCRYPT_H_
#define INC_ENCRYPT_H_

#include <stdint.h>
#include "stm32wbxx_hal.h"
#include "stm32wbxx_hal_rng.h"
#include "mbedtls/chachapoly.h"
#include "mbedtls/chacha20.h"
#include "mbedtls/gcm.h"
#include <stdbool.h>
#include "cmox_crypto.h"
#include "ecc/cmox_ecdh.h"
#include "ecc/cmox_ecc.h"
#include "hash/legacy_v3_sha256.h"
#include "ecc/legacy_v3_ecc.h"
#include "err_codes.h"


#define SCRATCH_SIZE 	512
#define ECC_CTX_SIZE  	512
#define PRIVKEY_SIZE 	32
#define PUBKEY_SIZE  	65
#define SECRET_SIZE  	32
#define TAG_SIZE 		16
#define AES_KEY_SIZE   	32

extern uint8_t ecdh_private[PRIVKEY_SIZE];
extern uint8_t ecdh_public[PUBKEY_SIZE];
extern uint8_t shared_secret[SECRET_SIZE];
extern uint8_t aes_key[AES_KEY_SIZE];

uint32_t get_micros();
int chacha_encrypt_and_tag(const unsigned char *in, size_t in_len, const unsigned char *aad, size_t aad_len, unsigned char *out, unsigned char tag[16]);
int chacha20_encrypt(const uint8_t *in, size_t len, uint32_t counter, uint8_t *out);
void cmox_init_once(void);
int aes_gcm_encrypt_and_tag(const uint8_t *in, size_t in_len, const uint8_t *aad, size_t aad_len, uint8_t *out_with_tag);

#endif /* INC_ENCRYPT_H_ */
