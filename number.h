#ifndef NUMBER_H
#define NUMBER_H

#include <stdint.h>
#include "anotation.h"

bignum_t* create_bignum(uint32_t bytes);
int free_bignum(bignum_t* pnum);

void print_bits(bignum_t* number);
void print_hex(bignum_t* number);

// creates an inverse of the num
bignum_t* create_inverse(bignum_t* num); 

// inverses the num
bignum_t* inverse(bignum_t* num);        

// creates an exact deep copy of num
bignum_t* create_copy(bignum_t* num);    

// copies arr values from to num
// if the to is bigger then the from, copies all the from blocks, sets other to 0
// if the from is bigger then the to, copies only the amount of blocks that to has 
//    copying starts from rightmost (big endian)
bignum_t* copy(bignum_t* to, bignum_t* from);

#endif // NUMBER_H
