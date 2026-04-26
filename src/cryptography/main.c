#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "number.h"
#include "numops.h"

int main() {
    bignum_t* num = create_bignum(UINT256);
    bignum_t* num2 = create_bignum(UINT256);

    num->arr[3] = 0xffffffffffffffff;
    num2->arr[0] = 0x0a;

    printf("num:        ");
    print_hex(num);
    printf("\n");


    printf("num2:       ");
    print_hex(num2);
    printf("\n");

//     bitshift_left(num, 1);

//     printf("num:        ");
//     print_hex(num);
//     printf("\n");
// 


//     bignum_t* multiplier = slow_mul(num, num2);
// 
//     printf("multiplier: ");
//     print_hex(multiplier);
//     printf("\n");
// 

    bignum_t* divider = slow_div(num, num2);

    printf("divider:    ");
    print_hex(divider);
    printf("\n");



    free_bignum(divider);
//     free_bignum(multiplier);
    free_bignum(num);
    free_bignum(num2);
    return 0;
}
