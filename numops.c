#include <stddef.h>
#include <stdio.h>

#include "number.h"
#include "numops.h"

int add(bignum_t* dst, bignum_t* src) {
    if (!dst || !src) return -1;

    int carry = 0;
    for (size_t i = 0; i < dst->arr_size; i++) {
        if (i >= src->arr_size) break;
        carry = __builtin_add_overflow(dst->arr[i], carry, &dst->arr[i]);

        if (carry) // happens only if the dst->arr[i] is only 1's
            dst->arr[i] += src->arr[i];
        else
            carry = __builtin_add_overflow(dst->arr[i], src->arr[i], &dst->arr[i]);
    }

    return carry;
}

int sub(bignum_t* to, bignum_t* from) {
    if (!to || !from) return -1;

    bignum_t* inversed = create_inverse(from);
    if (!inversed) return -1;

    int carry = 1;
    for (size_t i = 0; i < to->arr_size; i++) {
        if (!carry) break;
        carry = __builtin_add_overflow(to->arr[i], carry, &to->arr[i]);
    }

    add(to, inversed);

    free_bignum(inversed);
    return 0;
}

int strictmul(bignum_t* to, bignum_t* from) {
    if (!to || !from || to->arr_size != from->arr_size) return -1;

    uint64_t arr[to->arr_size];
    

    return 0;
}



