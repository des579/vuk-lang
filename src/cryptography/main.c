#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "number.h"
#include "numops.h"


int main() {
    bignum_t* n = create_bignum(UINT256);
    bignum_t* d = create_bignum(UINT256);

//     n->arr[3] = 0x1000000000000000;
    d->arr[3] = 0xf000000000000000;
    n->arr[3] = 0x1000000000000000;

    PRINT_NUM(n);
    PRINT_NUM(d);


    bignum_t* num = slow_div(n, d, NULL);

    PRINT_NUM(num);

    if (num)
        free_bignum(num);
    free_bignum(d);
    free_bignum(n);
    return 0;
}

