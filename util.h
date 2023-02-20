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
    FALSE, TRUE
}Boolean;

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
    ERR_FAIL_READING, ERR_F_NAME, ERR_S_NAME, ERR_ID, ERR_PHONE, ERR_DATE, ERR_DEBT, NO_ERROR

}Set_Errors;

typedef enum
{
    ID_BAD_LEN, ID_NOT_NUMBER, ID_NO_ERROR
}Errors_ID;

typedef enum
{
    PHONE_BAD_LEN, PHONE_NOT_NUMBER, PHONE_NOT_BEGIN_WITH_ZERO, PHONE_NO_ERROR
}Errors_PHONE;

typedef enum
{
    DATE_BAD_FORMAT, DATE_NO_ERROR
}Errors_DATE;

typedef enum
{
    DEBT_IS_NOT_NUMBER, DEBT_BAD_LEN, DEBT_NO_ERROR
}Errors_DEBT;


typedef enum
{
    NEW_CUSTOMER, UPDATE_PHONE, UPDATE_DEBT, ID_ALREADY_EXIST_WITH_DIFF_NAME, ERROR_WITH_FILE

}Set_Insert_Db_Message;

typedef struct
{
    Set_Errors error;
    Set_Insert_Db_Message succes;
}Set_request;

typedef struct
{
    Fields field;
    Operators operator;
    // Refactor
    Boolean error_with_args;
    // End refactor
    char arg[MAX_STR_LEN];
}Select_request;

typedef struct
{
    unsigned int no_error;
    Errors_DATE date;
    Errors_DEBT debt;
    Errors_ID id;
    Errors_PHONE phone;

}Customer_Fields_Errors;


Set_Errors parse_set(char *set_command, Customer *customer);

Errors_ID validate_ID(char id[]);

Errors_DATE validate_Date(char date[]);

Errors_PHONE validate_Phone(char phone[]);

Errors_DEBT validate_Debt(char debt[]);

void display_fields_error_message(Customer_Fields_Errors * fields_error);

void display_set_error_message(Set_Errors set_err);

void validate_fields(Customer *customer, Customer_Fields_Errors * tmp);

void to_lower_str(char *str);

int is_digit_str(const char * str);

MenuChoice parse_first(char * arr);

void parse_select(char *arr, Select_request *request);

void set_operator(char *arr, Select_request *request);

#endif