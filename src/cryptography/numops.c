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
    for (size_t i = 0; i < inversed->arr_size; i++) {
        if (!carry) break;
        carry = __builtin_add_overflow(inversed->arr[i], carry, &inversed->arr[i]);
    }

    add(to, inversed);

    free_bignum(inversed);
    return 0;
}

bignum_t* slow_mul(bignum_t* a, bignum_t* b) {
    if (!a || !b || a->arr_size != b->arr_size) return NULL;

    bignum_t* num = create_bignum(a->number_size);
    bignum_t* adder = create_copy(a);
    if (!num || !adder) return NULL;

    for (size_t i = 0; i < b->number_size*8; i++) {
        if (((b->arr[i >> 6] >> (i & 63)) & 1) == 0) {
            bitshift_left(adder, 1);
            continue;
        }

        add(num, adder);
        bitshift_left(adder, 1);
    }
    
    free_bignum(adder);
    return num;
}


bignum_t* slow_div(bignum_t* a, bignum_t* b, bignum_t* remainder) {
    if (!a || !remainder || !b || a->arr_size != b->arr_size
        || (remainder && a->arr_size != remainder->arr_size)) return NULL;

    bignum_t* q = create_bignum(a->arr_size * 8);
    if (!q) return NULL;

    SET_NUM_0(remainder);
    
    size_t numbits = a->arr_size * 64;
    for (size_t _ = 0; _ < numbits; _++) {
        size_t i = numbits - 1 - _;

        bitshift_left(remainder, 1);
        remainder->arr[0] |= ((a->arr[i >> 6] >> (i & 63)) & 1); // set the first bit to 0, to the ith bit of a

        if (is_bigger(remainder, b) || is_equals(remainder, b)) {
            sub(remainder, b);
            q->arr[i >> 6] |= (1 << (i & 63));
        }
    }

    return q;
}

int strictmul(bignum_t* to, bignum_t* from) {
    if (!to || !from || to->arr_size != from->arr_size) return -1;
    return 0;
}




