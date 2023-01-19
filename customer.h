#ifndef CUSTOMER_H
#define CUSTOMER_H

#define MAX_STR_LEN 50
#define PHONE_LEN 10
#define ID_LEN 9
#define MAX_DEBT_LEN 10

typedef struct
{
    char first_name[MAX_STR_LEN];
    char second_name[MAX_STR_LEN];

    char id[ID_LEN + 1];
    char phone_number[PHONE_LEN + 1];

    unsigned day,month,year; // Date field

    char debt[MAX_DEBT_LEN]; // char to avoid bad input like: 100mklfas
} Customer;


void print_customer(Customer *c);


#endif