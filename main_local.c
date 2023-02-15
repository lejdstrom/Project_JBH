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

    Vector_customer *data_base = NULL;
    data_base = init_db(argv[1]);
    if (!data_base)
    {
        printf("error with creating data base from file %s\n", argv[1]);
    }

    print_db(data_base);

    char buffer[BUFFER_SIZE] = {};
    char copy_buffer[BUFFER_SIZE] = {};
    char delimiters[] = {" ,\n"};
    int flag = 1;

    // select request
    Select_request request = {};
    char *part;
    Vector_customer request_answer = {};

    // set request
    Customer_Fields_Errors customer_fields_errors = {};
    Set_Errors set_errors;
    Set_Insert_Db_Message set_message;
    Customer customer_tmp = {};
    char tmp_buff[BUFFER_SIZE] = {};

    while (flag)
    {
        PROMPT
        memset(buffer, 0, sizeof(buffer));

        fgets(buffer, BUFFER_SIZE - 1, stdin);
        strcpy(copy_buffer, buffer);
        to_lower_str(copy_buffer);

        part = strtok(copy_buffer, delimiters);

        switch (parse_first(part))
        {
        case PRINT:
            print_db(data_base);
            break;

        case SELECT:
            // parse the rest of the string
            parse_select(part, &request);
            if (request.field == UNKNOW_FIELD || request.operator== UNKNOW_OP)
            {
                puts("problem with your request, try again");
                break;
            }

            vector_init(&request_answer);

            answer_request(data_base, &request_answer, function_dispatcher(&request), &request);

            if (request_answer.total > 0)
            {
                print_db(&request_answer);
                vector_free(&request_answer);
            }

            break;

        case SET:

            strcpy(tmp_buff, buffer + strlen(part));
            set_errors = parse_set(tmp_buff, &customer_tmp);

            if (set_errors == NO_ERROR)
            {
                validate_fields(&customer_tmp, &customer_fields_errors);

                if (customer_fields_errors.no_error)
                {
                    // add to data base
                    set_message = add_customer_to_db(data_base, &customer_tmp, argv[1]);
                    display_insert_db_message(set_message, &customer_tmp);
                }
                else
                {
                    // display adapted error message
                    display_fields_error_message(&customer_fields_errors);
                }
            }
            // display adapted error message, if parse_set failed
            else
            {
                display_set_error_message(set_errors, print_to_stdout, 0);
            }
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

    return 0;
}