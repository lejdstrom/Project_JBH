#ifndef DATA_BASE_H
#define DATA_BASE_H

#include "vector_customer.h"
#include "util.h"

#define BUFFER_SIZE 256


Vector_customer * init_db(char path[]);
void free_db(Vector_customer *v);
void print_db(Vector_customer *v);
int cmp_debt(void* c1, void *c2);





#endif