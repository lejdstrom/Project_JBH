#include "vector_customer.h"

void vector_init(Vector_customer *v)
{
    v->size = 0;
    v->data = NULL;
}

void vector_resize(Vector_customer *v, unsigned new_size)
{
    
}
void vector_add(Vector_customer *v, Customer * c);