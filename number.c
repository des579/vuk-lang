#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>


#include "number.h"


bignum_t* create_bignum(uint32_t bytes) {
    if (bytes <= 0) return NULL;

    uint64_t *arr = calloc(bytes / 8, 8);
    if (!arr) return NULL;

    bignum_t* number = malloc(sizeof(bignum_t));
    if (!number) return NULL;

    number->arr = arr;
    number->arr_size = bytes/8;
    number->number_size = bytes;

    return number;
}

int free_bignum(bignum_t* pnum) {
    if (!pnum) return -1;

    if (pnum->arr) free(pnum->arr);
    free(pnum);
    return 0;
}

bignum_t* create_inverse(bignum_t* num) {
    bignum_t* new = create_bignum(num->arr_size * 8);
    if (!new)
        return NULL;

    for (size_t i = 0; i < new->arr_size; i++)
        new->arr[i] = UINT64_MAX - num->arr[i];
    return new;
}

bignum_t* inverse(bignum_t* num) {
    if (!num) return NULL;
    for (size_t i = 0; i < num->arr_size; i++) {
        num->arr[i] = UINT64_MAX - num->arr[i];
    }

    return num;
}

int bitshift_left(bignum_t* num, size_t n) {
    if (!num) return -1;
    size_t b = n >> 6; // 011111 = 63 <- that is the remainder
    size_t remainder = n & 63;

    size_t i;
    if (b != 0) {
        for (i = 0; i < num->arr_size; i++) {
            int block = num->arr_size - i - 1;
            int from = block - b;
            if (from < 0) {
                num->arr[block] = 0;
                continue;
            }

            num->arr[block] = num->arr[from];
        }
    }


    if (remainder == 0) return 0;

    uint64_t arr[num->arr_size];
    for (i = 0; i < num->arr_size; i++) {
        arr[i] = num->arr[i];
        num->arr[i] = 0;
    }

    size_t block;
    for (i = 0; i < num->arr_size - 1; i++) {
        block = num->arr_size - 1 - i;
        num->arr[block] = (arr[block] << n) | (arr[block - 1] >> (64 - n));
    }
    num->arr[block - 1] = arr[block - 1] << n; 
    
    return 0;
}


int bitshift_right(bignum_t* num, size_t n) {
    if (!num) return -1;
    size_t b = n >> 6; // 011111 = 63 <- that is the remainder
    size_t remainder = n & 63;

    size_t i;
    if (b != 0) {
        for (i = 0; i < num->arr_size; i++) {
            if (i + 1 >= num->arr_size) {
                num->arr[i] = 0;
                continue;
            }

            num->arr[i] = num->arr[i + 1];
        }
    }


    if (remainder == 0) return 0;

    uint64_t arr[num->arr_size];
    for (i = 0; i < num->arr_size; i++) {
        arr[i] = num->arr[i];
        num->arr[i] = 0;
    }

    size_t block;
    for (i = 0; i < num->arr_size - 1; i++) {
        num->arr[i] = (arr[i] >> n) | (arr[i + 1] << (64 - n));
    }
    num->arr[i + 1] = arr[i + 1] >> n; 
    
    return 0;
}


void print_bits(bignum_t* number) {
    for (size_t i = 0; i < number->arr_size; i++) {
        for (size_t j = 0; j < 64; j++) {
            printf("%d", (number->arr[number->arr_size - i - 1] >> (63 - j)) & 1);
        }
    }
}

void print_hex(bignum_t* number) {
    for (size_t i = 0; i < number->arr_size; i++) {
        printf("%016" PRIx64, number->arr[number->arr_size - i - 1]);
        printf(" ");
    }
}


