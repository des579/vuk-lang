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
    bignum_t* adder = create_bignum(a->number_size);
    if (!num || !adder) return NULL;

    for (size_t i = 0; i < b->number_size*8; i++) {
        if (((b->arr[i >> 6] >> (i & 63)) & 1) == 0)
            continue;

        for (size_t j = 0; j < a->arr_size; j++) {
            adder->arr[j] = a->arr[j];
        }

        bitshift_left(adder, i);
        add(num, adder);
    }
    
    free_bignum(adder);
    return num;
}


bignum_t* slow_div(bignum_t* a, bignum_t* b) {
    if (!a || !b || a->arr_size != b->arr_size) return NULL;

    bignum_t* num = create_bignum(a->number_size);
    bignum_t* adder = create_bignum(a->number_size);
    if (!num || !adder) return NULL;

    for (size_t i = 0; i < b->number_size*8; i++) {
        if (((b->arr[i >> 6] >> (i & 63)) & 1) == 0)
            continue;

        printf("working when 1 at %lu...\n", i);
        for (size_t j = 0; j < a->arr_size; j++) {
            adder->arr[j] = a->arr[j];
        }

        bitshift_right(adder, i);
        printf("adder: ");
        print_hex(adder);
        printf("\n");
        add(num, adder);
    }
    
    free_bignum(adder);
    return num;
}

int strictmul(bignum_t* to, bignum_t* from) {
    if (!to || !from || to->arr_size != from->arr_size) return -1;


    

    return 0;
}




