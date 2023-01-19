#ifndef VECTOR_CUSTOMER_H
#define VECTOR_CUSTOMER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"

#define VECT_INIT_CAPACITY 4

typedef struct
{
    Customer * data;
    unsigned total;
    unsigned capacity;
}Vector_customer;

void vector_init(Vector_customer *v);
void vector_resize(Vector_customer *v, unsigned new_size);
void vector_add(Vector_customer *v, Customer * c);
void vector_add_by_value(Vector_customer *v, Customer c);

void vector_print(Vector_customer *v);
int index_of_id(Vector_customer *v, char * id);


#endif