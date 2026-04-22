#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "number.h"
#include "numops.h"

int main() {
    bignum_t* num = create_bignum(UINT256);
    bignum_t* num2 = create_bignum(UINT256);

    num->arr[3] = 0xfffffffffffffffe;
    num2->arr[3] = 0xffffffffffffffff;

    print_hex(num);
    printf("\n");

    sub(num, num2);

    print_hex(num);
    printf("\n");

    free_bignum(num);
    free_bignum(num2);
    return 0;
}
