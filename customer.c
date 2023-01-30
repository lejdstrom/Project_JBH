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