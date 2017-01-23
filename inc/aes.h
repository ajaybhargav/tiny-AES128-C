#ifndef _AES_H_
#define _AES_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


// #define the macros below to 1/0 to enable/disable the mode of operation.
//
// CBC enables AES128 encryption in CBC-mode of operation and handles 0-padding.
// ECB enables the basic ECB 16-byte block algorithm. Both can be enabled simultaneously.

// The #ifndef-guard allows it to be configured before #include'ing or at compile time.
#ifndef CBC
  #define CBC 1
#endif

#ifndef ECB
  #define ECB 1
#endif

#ifndef CMAC
  #define CMAC 1
#endif

/*****************************************************************************/
/* Defines:                                                                  */
/*****************************************************************************/
// The number of columns comprising a state in AES. This is a constant in AES. Value=4
#define Nb 4
// The number of 32 bit words in a key.
#define Nk 4
// Key length in bytes [128 bit]
#define KEYLEN 16
// The number of rounds in AES Cipher.
#define Nr 10

typedef uint8_t aes_state_t[4][4];
typedef struct _aes_t aes_t;

struct _aes_t {
	// state - array holding the intermediate results during decryption.
	aes_state_t* state;

	// The array that stores the round keys.
	uint8_t RoundKey[176];

	// The Key input to the AES Program
	const uint8_t* Key;

#if defined(CBC) && CBC
	// Initial Vector used only for CBC mode
	uint8_t Iv[KEYLEN];
#endif
};

#if defined(ECB) && ECB

void AES128_ECB_encrypt(aes_t *aes, const uint8_t* input, const uint8_t* key, uint8_t *output);
void AES128_ECB_decrypt(aes_t *aes, const uint8_t* input, const uint8_t* key, uint8_t *output);

#endif // #if defined(ECB) && ECB


#if defined(CBC) && CBC

void AES128_CBC_encrypt_buffer(aes_t *aes, uint8_t* output, uint8_t* input, uint32_t length, const uint8_t* key, const uint8_t* iv);
void AES128_CBC_decrypt_buffer(aes_t *aes, uint8_t* output, const uint8_t* input, uint32_t length, const uint8_t* key, const uint8_t* iv);

/* These variants encrypt and decrypt the data block in-place.
 * The data block length MUST be a multiple of the algorithm block size (16 bytes) 
 * The return value will be non-zero if the length is incorrect.
 * For the decypt function, the iv data must be writable, and will be modified on return.
 */
uint8_t AES128_CBC_encrypt_inplace(aes_t *aes, uint8_t* data, size_t length, const uint8_t* key, const uint8_t* iv);
uint8_t AES128_CBC_decrypt_inplace(aes_t *aes, uint8_t* data, size_t length, const uint8_t* key, const uint8_t* iv);

#endif // #if defined(CBC) && CBC

#if defined(CMAC) && CMAC

void AES128_CBC_encrypt_block(aes_t *aes, uint8_t* output, uint8_t* input, const uint8_t* key);
void AES128_CMAC_generate_subkey(aes_t *aes, uint8_t* K1, uint8_t* K2, const uint8_t* key);
void AES128_CMAC(aes_t *aes, uint8_t* mac, uint8_t* message, uint32_t msgLen, uint8_t* key);

#endif // #if defined(CMAC) && CMAC

#ifdef __cplusplus
}
#endif

#endif //_AES_H_
