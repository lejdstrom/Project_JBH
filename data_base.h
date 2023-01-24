#ifndef DATA_BASE_H
#define DATA_BASE_H

#include "util.h"
#include "vector_customer.h"

#define BUFFER_SIZE 256


Vector_customer * init_db(char path[]);
void free_db(Vector_customer *v);
void print_db(Vector_customer *v);
int cmp_debt_sort(void* c1, void *c2);

typedef int(*cmp_func)(Customer *c, Operators op, char *args);

void answer_request(Vector_customer *data_base, Vector_customer *out, cmp_func, Select_request *request);

cmp_func function_dispatcher(Select_request *request);

int cmp_first_name(Customer *c, Operators op, char *arg);
int cmp_second_name(Customer *c, Operators op, char *arg);
int cmp_date(Customer *c, Operators op, char *arg);
int cmp_id(Customer *c, Operators op, char *arg);
int cmp_debt(Customer *c, Operators op, char *arg);
int cmp_phone(Customer *c, Operators op, char *arg);

/*
void srch_first_name(Vector_customer *data_base, Vector_customer *out, Operators op, char *arg);
void srch_second_name(Vector_customer *data_base, Vector_customer *out, Operators op, char *arg);
void srch_id();
*/




#endif