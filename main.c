#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "number.h"
#include "numops.h"

int main() {
    bignum_t* num = create_bignum(UINT256);
    bignum_t* num2 = create_bignum(UINT256);

    num->arr[2] = 0xffffffffffffffff;

    print_hex(num);
    printf("\n");

    bitshift_right(num, 63);

    print_hex(num);
    printf("\n");

    free_bignum(num);
    free_bignum(num2);
    return 0;
}
