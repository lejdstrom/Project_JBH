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
        
        /*
        Customer tmp = {};

        for (int i = v->size; i < new_size; i++)
        {
            v->data[i] = tmp;
        }
        */
       if(tmp)
       {
            v->capacity = new_capacity;
            v->data = tmp;
       }
    }
    /*
    *   downsizing logic
    *   not needed now
    *

    else 
    {


    }

    */

}

void vector_add_by_value(Vector_customer *v, Customer c)
{
    int index = index_of_id(v, c.id);

    if (index >= 0) // found in our data base
    {
        // update 
        int a = atoi(v->data[index].debt);
        int b = atoi(c.debt);

        int result = a+b;

        snprintf(v->data[index].debt, ID_LEN, "%d", result);
    }
    else
    {
        
        if (v->capacity == v->total)
        {
            vector_resize(v, v->capacity * 2);
        }

        v->data[v->total++] = c;
    }
}


void vector_add(Vector_customer *v, Customer * c)
{
    int index = index_of_id(v, c->id);

    if (index >= 0) // found in our data base
    {
        // update 
        int a = atoi(v->data[index].debt);
        int b = atoi(c->debt);

        int result = a+b;

        snprintf(v->data[index].debt, ID_LEN, "%d", result);
    }
    else
    {
        
        if (v->capacity == v->total)
        {
            vector_resize(v, v->capacity * 2);
        }

        v->data[v->total++] = *c;
        
    }
    
    /*
    if(!v->data)
    {
        v->data = malloc(sizeof(Customer));
        v->data[0] = *c;
        v->size = 1;
    }
    else
    {
        int index = index_of_id(v, c->id);

        if (index >= 0) // found in our data base
        {
            // update 
            // v->data[index].debt
        }
        else
        // not in our db
        // lets look for an empty slot
        {
            // look for an empty slot
            // the empty strings means an empty slot
            index = index_of_id(v, "");
            if (index >= 0) // found in our data base
            {
                v->data[index] = *c;
            }
            else
            {

            }


        }
        
        
    }
    */
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
    for (int i = 0; i < v->total; i++)
    {
        print_customer(&v->data[i]);
    }
    puts("");
}