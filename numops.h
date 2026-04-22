#ifndef NUMBER_OPERATIONS_H
#define NUMBER_OPERATIONS_H

#include "number.h"

int add(bignum_t* to, bignum_t* from);
int sub(bignum_t* to, bignum_t* from);


/*
 * both multiplies restrict the action on the number sizes
 * if the number sizes (num->size or num->arr_size) are different, then no multiplication
 * strictmul multiplies the from to to
 *
 * loselessymul creates a new num with the arr_size = 2*num->arr_size
 *                                         size = 2*num->size
 * loselessymul returns a pointer to a new number
 */
int strictmul(bignum_t* to, bignum_t* from);
bignum_t* loselessymul(bignum_t* a, bignum_t* b);

#endif // NUMBER_OPERATIONS_H
