#ifndef _NP_ASSERTS_H_
#define _NP_ASSERTS_H_



#define NP_ASSERT_BYTES_EQUAL(a,b,size) do { \
        unsigned char *_a = (unsigned char *)(a), *_b = (unsigned char *)(b); \
        size_t _s=0; \
        while( _s < (size) && *_a==*_b ){ _s++;_a++;_b++; } \
        if ( _s < (size) && *_a!=*_b ) \
            __np_assert_failed(__FILE__, __LINE__, \
            "NP_ASSERT_BYTES_EQUAL(" #a " (0x%02x), " #b " (0x%02x) at offset %lld)",*_a,*_b, _s); \
    } while(0)


#endif
