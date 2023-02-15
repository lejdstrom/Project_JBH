#include <stdio.h>
#include <stdlib.h>
#include "customer.h"

void print_customer(Customer *c)
{
    printf("%-10s %-15s id: %s phone: %s date: %s\t----\tdebt: %s\n",
    c->first_name,
    c->second_name,
    c->id,
    c->phone_number,
    c->date,
    c->debt
    );
}

// Customer c to array
// need that arr ptr must be abble to contain 
// all fields of customer struct
void customer_to_string(Customer *c, char *arr)
{
    if(!arr)
    {
        puts("you must assure that arrary is enough big");
    }

    sprintf(arr, "%-10s %-15s id: %s phone: %s date: %s\t----\tdebt: %s\n",
    c->first_name,
    c->second_name,
    c->id,
    c->phone_number,
    c->date,
    c->debt
    );
}