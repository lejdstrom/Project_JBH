#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_base.h"

#define PROMPT printf("-> ");



int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("please input file name !\n");
        return 1;
    }

    Vector_customer * data_base = NULL;
    data_base = init_db(argv[1]);

    if (!data_base)
    {
        printf("error with creating data base from file %s\n", argv[1]);
    }

    print_db(data_base);

    char buffer[BUFFER_SIZE]={};
    char copy_buffer[BUFFER_SIZE] = {};
    char pre_parsed_buff[BUFFER_SIZE]={};
    char delimiters[] = {" "};

    //PROMPT
    //fgets(buffer, BUFFER_SIZE-1, stdin);

    while (strncmp(buffer, "quit", 4))
    {
        PROMPT
        fgets(buffer, BUFFER_SIZE-1, stdin);
        strcpy(copy_buffer, buffer);
        to_lower_str(copy_buffer);
        printf("your input: %s\n", copy_buffer);
    }
    

    free_db(data_base);

    return 0;
}