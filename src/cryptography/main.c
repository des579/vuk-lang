#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "number.h"
#include "numops.h"


int main() {
    bignum_t* n = create_bignum(UINT128);
    bignum_t* d = create_bignum(UINT128);

    n->arr[1] = 0x00f0;
    d->arr[0] = 0xff03;

    PRINT_NUMHEX(n);
    PRINT_NUMHEX(d);    

    bignum_t* mult = slow_mul(n, d);
    PRINT_NUMHEX(mult);


    bignum_t* remainder = create_copy(n);
    bignum_t* div = slow_div(mult, n, remainder);

    printf("remainder: ");
    PRINT_NUMHEX(remainder);

    printf("div:     : ");
    PRINT_NUMHEX(div);


    free_bignum(remainder);
    free_bignum(div);
    free_bignum(mult);
    free_bignum(n);
    free_bignum(d);
    return 0;
}

