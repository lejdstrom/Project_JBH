#ifndef UTIL_H
#define UTIL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STR_LEN 50

typedef enum
{
    PRINT, SELECT, QUIT, SET, UNKNOW
}MenuChoice;

typedef enum
{
    EQUAL, NOT_EQUAL, GREATER, SMALLER, UNKNOW_OP
}Operators;

typedef enum
{
    FIRST_NAME, SECOND_NAME, ID, PHONE, DATE, DEBT, UNKNOW_FIELD
}Fields;

typedef struct
{
    Fields field;
    Operators operator;
    char arg[MAX_STR_LEN];
}Select_request;


void quick_sort(void* v, int size, int left, int right, int (*comp)(void*, void*));
void swap(void* v1, void* v2, int size);

void to_lower_str(char *str);


MenuChoice parse_first(char * arr);

void parse_select(char *arr, Select_request *request);

void set_operator(char *arr, Select_request *request);



#endif