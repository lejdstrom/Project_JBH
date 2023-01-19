#ifndef VECTOR_CUSTOMER_H
#define VECTOR_CUSTOMER_H

#include <stdio.h>
#include <stdlib.h>
#include "customer.h"

typedef struct
{
    Customer * data;
    unsigned size;
}Vector_customer;

void vector_init(Vector_customer *v);
void vector_resize(Vector_customer *v, unsigned new_size);
void vector_add(Vector_customer *v, Customer * c);


#endif