#ifndef DATA_BASE_H
#define DATA_BASE_H

#include "util.h"
#include "vector_customer.h"

#define BUFFER_SIZE 256


Vector_customer * init_db(char path[]);
void free_db(Vector_customer *v);
void print_db(Vector_customer *v);
int cmp_debt(void* c1, void *c2);

/*
void srch_first_name(Vector_customer *data_base, Vector_customer *out, Operators op, char *arg);
void srch_second_name(Vector_customer *data_base, Vector_customer *out, Operators op, char *arg);
void srch_id();
*/




#endif