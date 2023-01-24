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

    Vector_customer request_answer = {};

    if (!data_base)
    {
        printf("error with creating data base from file %s\n", argv[1]);
    }

    print_db(data_base);

    char buffer[BUFFER_SIZE] = {};
    char copy_buffer[BUFFER_SIZE] = {};
    char delimiters[] = {" ,\n"};
    int flag = 1;

    char * part;
    Select_request request = {};

    while (flag)
    {
        PROMPT
        memset(buffer, 0, sizeof(buffer));

        fgets(buffer, BUFFER_SIZE-1, stdin);
        strcpy(copy_buffer, buffer);

        buffer[strspn(buffer, "\n")] = 0;
        
        to_lower_str(copy_buffer);

        part = strtok(copy_buffer, delimiters);

        switch (parse_first(part))
        {
        case PRINT:
            print_db(data_base);
            // goto free buffer
            break;
        
        case SELECT:
            // parse the rest of the string
            parse_select(part, &request);
            if (request.field == UNKNOW_FIELD || request.operator == UNKNOW_OP)
            {
                puts("problem with your request, try again");
                break;
            }

            vector_init(&request_answer);
            
            answer_request(data_base, &request_answer, function_dispatcher(&request), &request);

            if(request_answer.total > 0)
            {
                print_db(&request_answer);
                vector_free(&request_answer);
            }

            break;
        
        case SET:
            // parse and check the res of the string
            break;

        case QUIT:
            flag = 0;
            break;

        case UNKNOW:
            puts("error you must choose between one of the 4 options: print, select, set, quit");
            break;
        }
        
    }


    free_db(data_base);
    //vector_free(&answer_request);

    return 0;
}