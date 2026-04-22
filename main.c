#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "number.h"
#include "numops.h"

int main() {
    bignum_t* num = create_bignum(UINT256);
    bignum_t* num2 = create_bignum(UINT256);

    num->arr[3] = 0xffffffffffffffff;
    num2->arr[3] = 0xfffffffffffffffe;

    printf("removing...\n");
    printf("  ");
    print_hex(num);
    printf("\n");
    printf("- ");
    print_hex(num2);
    printf("\n");

    sub(num, num2);
    printf("-----------------------------------------\n");
    printf("  ");
    print_hex(num);
    printf("\n");

    free_bignum(num);
    free_bignum(num2);
    return 0;
}
