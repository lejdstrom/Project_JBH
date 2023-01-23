#include "util.h"

void quick_sort(void *v, int size, int left, int right, int (*comp)(void *, void *))
{
    void *vt, *v3;
    int i, last, mid = (left + right) / 2;
    if (left >= right)
        return;
  
    // casting void* to char* so that operations 
    // can be done.
    void* vl = (char*)(v + (left * size));
    void* vr = (char*)(v + (mid * size));
    swap(vl, vr, size);
    last = left;
    for (i = left + 1; i <= right; i++) {
  
        // vl and vt will have the starting address 
        // of the elements which will be passed to 
        // comp function.
        vt = (char*)(v + (i * size));
        if ((*comp)(vl, vt) > 0) {
            ++last;
            v3 = (char*)(v + (last * size));
            swap(vt, v3, size);
        }
    }

    v3 = (char*)(v + (last * size));
    swap(vl, v3, size);
    quick_sort(v, size, left, last - 1, comp);
    quick_sort(v, size, last + 1, right, comp);
}

void swap(void *v1, void *v2, int size)
{
    // buffer is array of characters which will 
    // store element byte by byte
    char buffer[size];
  
    // memcpy will copy the contents from starting
    // address of v1 to length of size in buffer 
    // byte by byte.
    memcpy(buffer, v1, size);
    memcpy(v1, v2, size);
    memcpy(v2, buffer, size);
}

void to_lower_str(char *str)
{
    for ( ; *str; ++str) *str = tolower(*str);
}
