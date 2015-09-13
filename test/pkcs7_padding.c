#include <np.h>
#include "np-asserts.h"
#include "../pkcs7_padding.h"


static void test_pkcs7_padding_pads(void){
  uint8_t data[16] = {0xaa, 0x55 , 0xaa ,0x55 };
  uint8_t datalength = 4;
  uint8_t modulus = 16;
  uint8_t expected[16] = {0xaa, 0x55 , 0xaa ,0x55, 12,12,12,12,12,12,12,12,12,12,12,12 };
  
  int result = pkcs7_padding_pad_buffer( data, datalength, sizeof(data), modulus );
  NP_ASSERT_EQUAL( 12, result );
  NP_ASSERT_BYTES_EQUAL( expected, data, sizeof(data) );
}

static void test_pkcs7_padding_pads_one(void){
  uint8_t data[16] = {0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 , 0xaa ,0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 , 0xaa };
  uint8_t datalength = 15;
  uint8_t modulus = 16;
  uint8_t expected[16] = {0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 , 0xaa ,0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 , 0xaa, 0x01 };
  
  int result = pkcs7_padding_pad_buffer( data, datalength, sizeof(data), modulus );
  NP_ASSERT_EQUAL( 1, result );
  NP_ASSERT_BYTES_EQUAL( expected, data, sizeof(data) );
}

static void test_pkcs7_padding_pads_full(void){
  uint8_t data[16] = {0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 , 0xaa ,0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 , 0xaa, 0x55 };
  uint8_t datalength = 16;
  uint8_t modulus = 16;
  uint8_t expected[16] = {0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 , 0xaa ,0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 , 0xaa, 0x55 };
  
  int result = pkcs7_padding_pad_buffer( data, datalength, sizeof(data), modulus );
  NP_ASSERT_EQUAL( -16 , result );
  NP_ASSERT_BYTES_EQUAL( expected, data, sizeof(data) );
}

static void test_pkcs7_padding_pad_larger(void){
  uint8_t data[32] = {0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 , 0xaa, 0x55 };
  uint8_t datalength = 16;
  uint8_t modulus = 16;
  uint8_t expected[32] = {
    0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10
  };
  
  int result = pkcs7_padding_pad_buffer( data, datalength, sizeof(data), modulus );
  NP_ASSERT_EQUAL( 16 , result );
  NP_ASSERT_BYTES_EQUAL( expected, data, sizeof(data) );
}

static void test_pkcs7_padding_valid(void){
  uint8_t data[16] = {0xaa, 0x55 , 0xaa ,0x55, 12,12,12,12,12,12,12,12,12,12,12,12 };
  uint8_t modulus = 16;
  size_t data_length = 4;
  
  int result = pkcs7_padding_valid( data, data_length, sizeof(data), modulus );
  NP_ASSERT_EQUAL( 1, result );
}

static void test_pkcs7_padding_invalid_last(void){
  uint8_t data[16] = {0xaa, 0x55 , 0xaa ,0x55, 12,12,12,12,12,12,12,12,12,12,12,11 };
  uint8_t modulus = 16;
  size_t data_length = 4;
  
  int result = pkcs7_padding_valid( data, data_length, sizeof(data), modulus );
  NP_ASSERT_EQUAL( 0, result );
}

static void test_pkcs7_padding_invalid_first(void){
  uint8_t data[16] = {0xaa, 0x55 , 0xaa ,0x55, 11,12,12,12,12,12,12,12,12,12,12,12 };
  uint8_t modulus = 16;
  size_t data_length = 4;
  
  int result = pkcs7_padding_valid( data, data_length, sizeof(data), modulus );
  NP_ASSERT_EQUAL( 0, result );
}

static void test_pkcs7_padding_invalid_too_small(void){
  uint8_t data[6] = {0xaa, 0x55 , 0xaa ,0x55, 12, 12 };
  uint8_t modulus = 16;
  size_t data_length = 4;
  
  int result = pkcs7_padding_valid( data, data_length, sizeof(data), modulus );
  NP_ASSERT_EQUAL( 0, result );
}

static void test_pkcs7_padding_invalid_zero_too_small(void){
  uint8_t data[16] = {0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55 };
  uint8_t modulus = 16;
  size_t data_length = 16;
  
  int result = pkcs7_padding_valid( data, data_length, sizeof(data), modulus );
  NP_ASSERT_EQUAL( 0, result );
}

static void test_pkcs7_padding_valid_16(void){
  uint8_t data[32] = {
    0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10
  };
  uint8_t modulus = 16;
  size_t data_length = 16;
  
  int result = pkcs7_padding_valid( data, data_length, sizeof(data), modulus );
  NP_ASSERT_EQUAL( 1, result );
}
