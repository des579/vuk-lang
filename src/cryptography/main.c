#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "number.h"
#include "numops.h"


int main() {
    bignum_t* n = create_bignum(UINT128);
    bignum_t* d = create_bignum(UINT128);
    bignum_t* r = create_bignum(UINT128);

    n->arr[0] = 0xf000000000000000;
    d->arr[0] = 0x0000000000000002;

    printf("%d\n", is_bigger(n, d));
    printf("%d\n", is_equals(n, d));


    PRINT_NUMHEX(n);
    PRINT_NUMHEX(d);


    bignum_t* q = slow_div(n, d, r);

    printf("q: ");
    PRINT_NUMHEX(q);

    printf("r: ");
    PRINT_NUMHEX(r);

//     add(q, q);

    bignum_t* q_copy = create_copy(q);


    bignum_t* mult = slow_mul(q, q_copy);
    PRINT_NUMHEX(mult);


    free_bignum(mult);
    free_bignum(q_copy);
    free_bignum(q);
    free_bignum(r);
    free_bignum(d);
    free_bignum(n);
    return 0;
}

