#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>


#include "number.h"


bignum_t* create_bignum(uint16_t bytes) {
    if (bytes <= 0) return NULL;

    uint32_t blocks = bytes/8;
    uint64_t *arr = calloc(blocks, 8);
    if (!arr) return NULL;

    bignum_t* number = malloc(sizeof(bignum_t));
    if (!number) {
        free(arr);
        return NULL;
    }

    number->arr = arr;
    number->arr_size = blocks;
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
        new->arr[i] = ~num->arr[i];
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

    for (i = 0; i < num->arr_size - 1; i++) {
        num->arr[i] = (arr[i] >> n) | (arr[i + 1] << (64 - n));
    }

    num->arr[i] = arr[i] >> n; 
    
    return 0;
}

bignum_t* create_copy(bignum_t* num) {
    if (!num) return NULL;
    bignum_t* copy = create_bignum(num->arr_size * 8);
    if (!copy) return NULL;

    for (int i = 0; i < num->arr_size; i++)
        copy->arr[i] = num->arr[i];

    return copy;
}

// a > b?
int is_bigger(bignum_t* a, bignum_t* b) {
    if (!a || !b || a->arr_size != b->arr_size) return -1;

    int block = a->arr_size - 1;
    for (size_t i = 0; i < a->arr_size; i++) {
        if ((a->arr[block] == 0 && b->arr[block] == 0) || a->arr[block] == b->arr[block]) {
            block--;
            continue;
        }

        if (a->arr[block] > b->arr[block]) return 1;
        else return 0;
    }


    return 0; // only if a = 0, b = 0
}

// a < b?
int is_lower(bignum_t* a, bignum_t* b) {
    if (!a || !b || a->arr_size != b->arr_size) return -1;

    int block = a->arr_size - 1;
    for (size_t i = 0; i < a->arr_size; i++) {
        if ((a->arr[block] == 0 && b->arr[block] == 0) || a->arr[block] == b->arr[block]) {
            block--;
            continue;
        }

        if (a->arr[block] < b->arr[block]) return 1;
        else return 0;
    }

    return 0; // only if a = 0, b = 0
}

// a == b?
int is_equals(bignum_t* a, bignum_t* b) {
    if (!a || !b || a->arr_size != b->arr_size) return -1;

    for (size_t i = 0; i < a->arr_size; i++) {
        if (a->arr[i] != b->arr[i]) return 0;
    }

    return 1;
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


