#ifndef UTIL_H
#define UTIL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void quick_sort(void* v, int size, int left, int right, int (*comp)(void*, void*));
void swap(void* v1, void* v2, int size);

void to_lower_str(char *str);

typedef enum
{
    PRINT, SELECT, QUIT, SET, UNKNOW
}MenuChoice;

typedef enum
{
    EQUAL, NOT_EQUAL, GREATER, SMALLER
}Operators;

MenuChoice parse_first(char * arr);



#endif