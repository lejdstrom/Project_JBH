#ifndef DATA_BASE_H
#define DATA_BASE_H

#include "vector_customer.h"

#define BUFFER_SIZE 256


Vector_customer * init_db(char path[]);
void free_db(Vector_customer *v);





#endif