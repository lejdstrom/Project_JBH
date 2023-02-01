#ifndef UTIL_H
#define UTIL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "customer.h"

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

typedef enum
{
    ERR_F_NAME, ERR_S_NAME, ERR_ID, ERR_PHONE, ERR_DATE, ERR_DEBT, NO_ERROR

}Set_Errors;

typedef enum
{
    ID_ALREADY_EXIST_WITH_DIFF_NAME, ID_BAD_LEN, ID_NOT_NUMBER, ID_NO_ERROR
}Set_Errors_ID;

typedef enum
{
    PHONE_BAD_LEN, PHONE_NOT_NUMBER, PHONE_NO_ERROR
}Set_Errors_PHONE;

typedef enum
{
    DATE_BAD_FORMAT, DATE_UNREALISTIC /* 45/45/1000 */, DATE_NO_ERROR
}Set_Errors_DATE

typedef enum
{
    NEW_CUSTOMER, UPDATE_PHONE, UPDATE_DEBT

}Set_sucess;


typedef struct
{
    Set_Errors error;
    Set_sucess succes;
}Set_request;


typedef struct
{
    Fields field;
    Operators operator;
    char arg[MAX_STR_LEN];
}Select_request;


void quick_sort(void* v, int size, int left, int right, int (*comp)(void*, void*));
void swap(void* v1, void* v2, int size);

void to_lower_str(char *str);

int is_digit_str(const char * str);


MenuChoice parse_first(char * arr);

void parse_set(char *arr, Set_request * set_request, Customer *tmp);

void print_set_success_message();

void print_set_error_message();

void parse_select(char *arr, Select_request *request);

void set_operator(char *arr, Select_request *request);



#endif