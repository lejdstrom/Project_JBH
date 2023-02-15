#ifndef DATA_BASE_H
#define DATA_BASE_H

#include "util.h"
#include "vector_customer.h"

#define BUFFER_SIZE 256

Vector_customer *init_db(char path[]);
void free_db(Vector_customer *v);
void print_db(Vector_customer *v);
int cmp_debt_sort(void *c1, void *c2);

typedef int (*cmp_func)(Customer *c, Operators op, char *args);

void answer_request(Vector_customer *data_base, Vector_customer *out, cmp_func, Select_request *request);

void add_customer_to_vector(Vector_customer *v, Customer *c);

Set_Insert_Db_Message add_customer_to_db(Vector_customer *v, Customer *c, char path[]);

void display_insert_db_message(Set_Insert_Db_Message message, Customer *customer);

cmp_func function_dispatcher(Select_request *request);


void sort(Vector_customer *vector);

int cmp_first_name(Customer *c, Operators op, char *arg);
int cmp_second_name(Customer *c, Operators op, char *arg);
int cmp_date(Customer *c, Operators op, char *arg);
int cmp_date_helper(int d1, int m1, int y1, int d2, int m2, int y2);
int cmp_id(Customer *c, Operators op, char *arg);
int cmp_debt(Customer *c, Operators op, char *arg);
int cmp_phone(Customer *c, Operators op, char *arg);

#endif