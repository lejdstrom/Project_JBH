#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_base.h"

#define PROMPT printf("-> ");

typedef enum{

    QUIT, PRINT, SELECT, SET

} Options;

typedef enum
{
    EQUAL, NOT_EQUAL, GREATER, SMALLER
}Operators;


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

    char *bool_options[4] = {NULL}; 
    char *options[] = {"quit", "print", "select", "set"};

    char *bool_operators[4] = {NULL};
    char *operators[] = {"=", "!=", ">", "<"};

    int i = 0;
    int flag = 0;

    char * part;

    //PROMPT
    //fgets(buffer, BUFFER_SIZE-1, stdin);

    while (strncmp(buffer, "quit", 4))
    {
        PROMPT
        fgets(buffer, BUFFER_SIZE-1, stdin);
        //strcpy(copy_buffer, buffer);
        to_lower_str(buffer);


        for(int j=0; j<4; j++)
        {
            bool_options[j] = strstr(buffer, options[j]);
        }

        if(bool_options[QUIT])
        {
            puts("quit !");
        }
        else if(bool_options[PRINT])
        {
            puts("print !");
        }
        else if(bool_options[SELECT])
        {
            puts("select !");
            for(int j=0; j<4; j++)
            {
                bool_operators[j] = strstr(buffer, operators[j]);
            }

            if(bool_operators[EQUAL])
            {
                puts("equal !");

            }
            else if(bool_operators[NOT_EQUAL])
            {
                puts("not equal !");
            }
            else if(bool_operators[GREATER])
            {
            
                puts("greater !");   
            }
            else if(bool_operators[SMALLER])
            {
                
                puts("smaller !");
            }
            else
            {
                puts("error ! after select you need to input one of the 4 operators: >, =, <, !=");
            }



        }
        else if(bool_options[SET])
        {
            puts("set !");
        }
        else
        {
            puts("error you must choose between one of the 4 options: print, select, set, quit");
            memset(buffer, 0, BUFFER_SIZE);
            memset(bool_operators, 0, 4);
            memset(bool_options, 0, 4);
        }



    }
    

    free_db(data_base);

    return 0;
}