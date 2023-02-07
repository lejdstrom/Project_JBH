#include "vector_customer.h"

void vector_init(Vector_customer *v)
{
    v->capacity = VECT_INIT_CAPACITY;
    v->total = 0;
    v->data = malloc(sizeof(Customer) * v->capacity);
}

void vector_resize(Vector_customer *v, unsigned new_capacity)
{
    if(!v->data)
    {
        return;
    }

    if(new_capacity > v->capacity)
    {
        Customer *tmp = realloc(v->data, sizeof(Customer) * new_capacity);
        
       if(tmp)
       {
            v->capacity = new_capacity;
            v->data = tmp;
       }
    }
}

void vector_add_by_value(Vector_customer *vector, Customer customer)
{
    int index = index_of_id(vector, customer.id);

    if (index >= 0) // found in our data base
    {
        // update 
        int a = atoi(vector->data[index].debt);
        int b = atoi(customer.debt);

        int result = a+b;

        snprintf(vector->data[index].debt, ID_LEN, "%d", result);
    }
    else
    {
        
        if (vector->capacity == vector->total)
        {
            vector_resize(vector, vector->capacity * 2);
        }

        vector->data[vector->total++] = customer;
    }
}


void vector_add(Vector_customer *v, Customer * c)
{
    int index = index_of_id(v, c->id);

    if (index >= 0) // found in our data base
    {
        // update debt
        int a = atoi(v->data[index].debt);
        int b = atoi(c->debt);

        int result = a+b;

        if (result != a)
        {
            snprintf(v->data[index].debt, MAX_DEBT_LEN, "%d", result);
        }
        
        // update phone
        if (strcmp(v->data[index].phone_number, c->phone_number))
        {
             snprintf(v->data[index].phone_number, PHONE_LEN + 1, "%s", c->phone_number);
        }
    }
    else
    {
        
        if (v->capacity == v->total)
        {
            vector_resize(v, v->capacity * 2);
        }

        v->data[v->total++] = *c;
        
    }
}

// return index of the customer vector if found
// otherwise return -1
int index_of_id(Vector_customer *v, char * id)
{
    for (int i = 0; i < v->total; i++)
    {
        // same id
        if (!strncmp(v->data[i].id, id, 9))
        {
            return i;
        }
    }

    return -1;
}

void vector_print(Vector_customer *v)
{
    puts("");
    for (int i = 0; i < v->total; i++)
    {
        print_customer(&v->data[i]);
    }
    puts("");
}

void vector_free(Vector_customer *v)
{
    free(v->data);
}