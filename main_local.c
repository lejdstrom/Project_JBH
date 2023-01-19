#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("please input file name !\n");
        return 1;
    }

    char * csv_file_path = argv[1];

    printf("filename is  %s \n", csv_file_path);
    
    return 0;
}