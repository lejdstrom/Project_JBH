#include <stdio.h>
#include <stdlib.h>
#include "customer.h"

void print_customer(Customer *c)
{
    printf("%s %s id: %s phone: %s date: %u/%u/%u -- debt: %s\n",
    c->first_name,
    c->second_name,
    c->id,
    c->phone_number,
    c->day,
    c->month,
    c->year,
    c->debt
    );
}