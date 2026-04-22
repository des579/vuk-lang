#ifndef ANOTATION_H
#define ANOTATION_H

#include <stdint.h>

#define UINT256 32
#define UINT512 64
#define UINT1024 128

typedef struct {
    uint64_t *arr;
    size_t arr_size;
    size_t number_size;
} bignum_t;

typedef unsigned __int128 __uint128;

#endif
