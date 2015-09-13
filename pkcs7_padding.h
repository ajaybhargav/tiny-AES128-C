#ifndef _PKCS7_PADDING_H_
#define _PKCS7_PADDING_H_

#include <stdint.h>
#include <stddef.h>

/* Pad a buffer with bytes as defined in PKCS#7 
 * Returns the number of pad bytes added, or zero if
 * the buffer size is not large enough to hold the correctly padded data
 */
int pkcs7_padding_pad_buffer( uint8_t *buffer,  size_t data_length, size_t buffer_size, uint8_t modulus );

int pkcs7_padding_valid( uint8_t *buffer, size_t data_length, size_t buffer_size, uint8_t modulus );
#endif