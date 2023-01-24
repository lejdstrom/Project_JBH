#include "util.h"

void quick_sort(void *v, int size, int left, int right, int (*comp)(void *, void *))
{
    void *vt, *v3;
    int i, last, mid = (left + right) / 2;
    if (left >= right)
        return;

    // casting void* to char* so that operations
    // can be done.
    void *vl = (char *)(v + (left * size));
    void *vr = (char *)(v + (mid * size));
    swap(vl, vr, size);
    last = left;
    for (i = left + 1; i <= right; i++)
    {

        // vl and vt will have the starting address
        // of the elements which will be passed to
        // comp function.
        vt = (char *)(v + (i * size));
        if ((*comp)(vl, vt) > 0)
        {
            ++last;
            v3 = (char *)(v + (last * size));
            swap(vt, v3, size);
        }
    }

    v3 = (char *)(v + (last * size));
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
    for (; *str; ++str)
        *str = tolower(*str);
}

MenuChoice parse_first(char *arr)
{
    if (!strncmp(arr, "print", 5))
    {
        return PRINT;
    }
    else if (!strncmp(arr, "select", 6))
    {
        return SELECT;
    }

    else if (!strncmp(arr, "set", 3))
    {
        return SET;
    }
    else if (!strncmp(arr, "quit", 4))
    {
        return QUIT;
    }
    else
    {
        return UNKNOW;
    }
}

void set_operator(char *arr, Select_request *request)
{
    if (!arr)
    {
        puts("you must enter an operator !");
        request->operator= UNKNOW_OP;
        return;
    }

    if (!strncmp(arr, ">", 1))
    {
        request->operator= GREATER;
    }
    else if (!strncmp(arr, "<", 1))
    {
        request->operator= SMALLER;
    }
    else if (!strncmp(arr, "=", 1))
    {
        request->operator= EQUAL;
    }
    else if (!strncmp(arr, "!=", 2))
    {
        request->operator= NOT_EQUAL;
    }
    else
    {
        puts("unknow operator !");
        request->operator= UNKNOW_OP;
    }
}

void parse_select(char *arr, Select_request *request)
{
    char *part1 = strtok(NULL, " ");
    char *part2 = NULL; //strtok(NULL /*+ strlen(part1)*/, " ");
    char *part3 = NULL;

    
    if (!part1)
    {
        puts("you must enter a field after select");
        request->field = UNKNOW_FIELD;
        return;
    }
    

    if (!strncmp(part1, "first", 5))
    {
        part2 = strtok(NULL, " ");
        if (!strncmp(part2, "name", 4))
        {

            puts("first name !");

            // must be operator
            part3 = strtok(NULL, " ");
            set_operator(part3, request);
            request->field = FIRST_NAME;
        }
    }
    else if (!strncmp(part1, "second", 5))
    {
        part2 = strtok(NULL, " ");
        if (!strncmp(part2, "name", 4))
        {
            puts("second name !");
            request->field = SECOND_NAME;

            // must be operator
            part3 = strtok(NULL, " ");
            set_operator(part3, request);
        }
    }
    else if (!strncmp(part1, "id", 2))
    {
        puts("id !");
        request->field = ID;

        set_operator(part2, request);
    }
    else if (!strncmp(part1, "phone", 5))
    {

        puts("phone !");
        request->field = PHONE;
        set_operator(part2, request);
    }
    else if (!strncmp(part1, "date", 4))
    {
        puts("date !");
        request->field = DATE;
        set_operator(part2, request);
    }
    else if (!strncmp(part1, "debt", 4))
    {
        puts("debt !");
        request->field = DEBT;
        set_operator(part2, request);
    }
    else
    {

        puts("unknow field !");
        request->field = UNKNOW_FIELD;
    }
}
