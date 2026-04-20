#include <stddef.h>

#include "number.h"
#include "numops.h"

int add(bignum_t* dst, bignum_t* src) {
    if (!dst || !src) return -1;


    int carry = 0;
    for (size_t i = dst->arr_size - 1; i >= 0; i--) {
        if (i >= src->arr_size) break;
        carry = __builtin_add_overflow(dst->arr[i], carry, &dst->arr[i]);

        if (carry) // happens only if the dst->arr[i] is only 1's
            dst->arr[i] += src->arr[i];
        else
            carry = __builtin_add_overflow(dst->arr[i], src->arr[i], &dst->arr[i]);
    }

    return 0;
}

int sub(bignum_t* dst, bignum_t* src) {
    if (!dst || !src) return -1;

    bignum_t* inversed = create_inverse(src);
    if (!inversed) return -1;

    int carry = 1;
    for (size_t i = inversed->arr_size - 1; i >= 0; i--) {
        if (!carry) break;
        carry = __builtin_add_overflow(inversed->arr[i], carry, &inversed->arr[i]);
    }


    add(dst, inversed);
    free_bignum(inversed);
    return 0;
}

int mul(bignum_t* to, bignum_t* from) {
    if (!to || !from || to->arr_size != from->arr_size) return -1;

    unsigned __int128 arr[to->arr_size][to->arr_size];

    for (size_t i = 0; i < to->arr_size; i++) {
        for (size_t j = 0; j < from->arr_size; j++) {

        }
    }

    return 0;
}



