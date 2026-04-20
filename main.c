#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "number.h"
#include "numops.h"

int main() {
    bignum_t *number = create_bignum(UINT256);
    bignum_t *number2 = create_bignum(UINT256);
    number2->arr[1] = 0xffffffffffffffff;

    add(number, number2);
    print_hex(number);
    printf("\n");



    add(number, number2);
    print_hex(number);
    printf("\n");

    sub(number, number2);
    print_hex(number);
    printf("\n");

    sub(number, number2);
    print_hex(number);
    printf("\n");

    sub(number, number2);
    print_hex(number);
    printf("\n");
//     add(number, number2);
//     add(number, number2);


    free_bignum(number);
    free_bignum(number2);
    return 0;
}
