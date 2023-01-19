#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "customer.h"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("please input file name !\n");
        return 1;
    }

    char * csv_file_path = argv[1];
    FILE * f = fopen(csv_file_path, "r");

    if (!f)
    {
        printf("error with reading <%s> file\n", csv_file_path);
    }





    
    return 0;
}