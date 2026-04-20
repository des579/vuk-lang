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

void print_bits(bignum_t* number) {
    for (size_t i = 0; i < number->arr_size; i++) {
        for (size_t j = 0; j < 63; j++) {
            printf("%d", (number->arr[i] >> j) & 1);
        }
    }
}

void print_hex(bignum_t* number) {
    for (size_t i = 0; i < number->arr_size; i++) {
        printf("%016" PRIx64, number->arr[i]);
        printf(" ");
    }
}


