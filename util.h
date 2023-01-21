#ifndef UTIL_H
#define UTIL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quick_sort(void* v, int size, int left, int right, int (*comp)(void*, void*));
void swap(void* v1, void* v2, int size);

#endif