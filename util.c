#include "util.h"

Set_Errors parse_set(char set_command[], Customer *customer)
{
    // we except 6 fields
    int read = sscanf(set_command, " first name=%49[^,], second name=%49[^,], id=%9[^,], phone=%10[^,], date=%10[^,], debt=%10[^\n]",
                  customer->first_name,
                  customer->second_name,
                  customer->id,
                  customer->phone_number,
                  customer->date,
                  customer->debt
                  );

    switch (read)
    {
    case 0:
        return ERR_FAIL_READING;
    
    case 1:
        return ERR_F_NAME;

    case 2:
        return ERR_S_NAME;

    case 3:
        return ERR_ID;

    case 4:
        return ERR_PHONE;
    
    case 5:
        return ERR_DATE;

    case 6:
        puts("we read all the fields !");
        return NO_ERROR;
    }
}

// sock must be set to 0 for stdout
void print_to_stdout(char *string, int sock)
{
    if(!sock)
        printf("%s\n", string);
}

// send string to client connected to sock
void print_to_client(char string[], int sock)
{
    int n;

    if(sock)
    {               // &string
        n = send(sock, string, strlen(string), 0);
    }
}

Set_Errors_ID validate_ID(char id[])
{
    int id_len = strlen(id);

    if(!is_digit_str(id))
    {
        return ID_NOT_NUMBER;
    }

    if( id_len > 9 || id_len < 9 )
    {
        return ID_BAD_LEN;
    }

    // id is a number, and id len == 10

    return ID_NO_ERROR;

}

Set_Errors_DATE validate_Date(char date[])
{

    int date_len = strlen(date);

    if (date_len > 10 || date_len < 10)
    {
        return DATE_BAD_FORMAT;
    }
    
    int bad_formated = 0;

    int day = atoi(date);
    int month = atoi(date + 3);
    int year = atoi(date + 6);

    if(day > 31 || day < 1)
    {
        bad_formated = 1;
    }

    if (month > 12 || month < 1)
    {
        bad_formated = 1;
    }

    if (year > 2050 || year < 2000)
    {
        bad_formated = 1;
    }

    if (bad_formated)
    {
        return DATE_BAD_FORMAT;
    }
    else
    {
        return DATE_NO_ERROR;
    }
}

Set_Errors_PHONE validate_Phone(char phone[])
{
    int phone_len = strlen(phone);

    if(phone_len > 10 || phone_len < 10)
    {
        return PHONE_BAD_LEN;
    }

    if(!is_digit_str(phone))
    {
        return PHONE_NOT_NUMBER;
    }

    if(phone[0] != '0')
    {
        return PHONE_NOT_BEGIN_WITH_ZERO;
    }

    // phone start with zero, and is a number and len == 10

    return PHONE_NO_ERROR;
}

Set_Errors_DEBT validate_Debt(char debt[])
{
    int debt_len = strlen(debt);

    if(debt_len > 10 || debt_len < 1)
    {
        return DEBT_BAD_LEN;
    }

    if(debt[0] == '-')
    {
        if (!is_digit_str(debt + 1))
        {
            return DEBT_IS_NOT_NUMBER;
        }
        else
        {
            return DEBT_NO_ERROR;
        }
        
    }
    else if (!is_digit_str(debt))
    {
        return DEBT_IS_NOT_NUMBER;
    }

    return DEBT_NO_ERROR;
}

void display_fields_error_message(Customer_Fields_Errors *fields_error, print_function print_func, int sock)
{
    switch (fields_error->date)
    {
    case DATE_NO_ERROR:
        break;
    
    case DATE_BAD_FORMAT:
        print_func("date should be formated : dd/mm/yyyy\nof course day month and year should be valid", sock);
        break;
    }

    switch (fields_error->debt)
    {
    case DEBT_NO_ERROR:
        break;
    
    case DEBT_IS_NOT_NUMBER:
        print_func("debt should be a number", sock);
        break;

    case DEBT_BAD_LEN:
        print_func("debt is to long", sock);
        break;
    }

    switch (fields_error->id)
    {
    case ID_NO_ERROR:
        break;

    case ID_NOT_NUMBER:
        print_func("id should be a number", sock);
        break;

    case ID_BAD_LEN:
        print_func("id len should be 10", sock);
        break;
    }

    switch (fields_error->phone)
    {
    case PHONE_NO_ERROR:
        break;

    case PHONE_BAD_LEN:
        print_func("phone len should be 10", sock);
        break;

    case PHONE_NOT_BEGIN_WITH_ZERO:
        print_func("phone number must start with zero", sock);
        break;

    case PHONE_NOT_NUMBER:
        print_func("phone should be only number", sock);
        break;
    }
}

void display_set_error_message(Set_Errors set_err, print_function print_func, int sock)
{
    // function ptr and socket
    switch(set_err)
    {
        case ERR_FAIL_READING:
            print_func("problem with set command: 0 fields were read", sock);
            return;
        
        case ERR_F_NAME:
            print_func("we read only first name", sock);
            return;

        case ERR_S_NAME:
            print_func("we read until second name", sock);
            return;

        case ERR_ID:
            print_func("we read until id", sock);
            return;
        
        case ERR_PHONE:
            print_func("we read until phone", sock);
            return;

        case ERR_DATE:
            print_func("we read until date", sock);
            return;
    }
}

void validate_fields(Customer *customer, Customer_Fields_Errors * tmp)
{
    tmp->date = validate_Date(customer->date);
    tmp->debt = validate_Debt(customer->debt);
    tmp->id = validate_ID(customer->id);
    tmp->phone = validate_Phone(customer->phone_number);

    if(tmp->date == DATE_NO_ERROR && tmp->debt == DEBT_NO_ERROR && tmp->id == ID_NO_ERROR && tmp->phone == PHONE_NO_ERROR)
    {
        tmp->no_error = 1;
    }
    else
    {
        tmp->no_error = 0;
    }
    
    return;
}

void to_lower_str(char *str)
{
    for (; *str; ++str)
        *str = tolower(*str);
}

int is_digit_str(const char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
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
        puts("error you must enter an operator !");
        request->operator= UNKNOW_OP;
        return;
    }

    if (strlen(arr) > 2)
    {
        puts("error you must enter a valid operator (>, <, = , !=)");
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

void parse_select(char *arr, Select_request *request, print_function print_func, int sock)
{
    char *part1 = strtok(NULL, " ");
    char *part2 = NULL; // strtok(NULL /*+ strlen(part1)*/, " ");
    char *part3 = NULL;
    char *part4 = NULL;

    if (!part1)
    {
        print_func("you must enter a field after select", sock);
        request->field = UNKNOW_FIELD;
        return;
    }

    if (!strcmp(part1, "first"))
    {
        part2 = strtok(NULL, " ");

        // not sure needed
        if (!part2)
        {
            print_func("error you should insert a space after first !", sock);
            request->field = UNKNOW_FIELD;
            return;
        }

        if (!strncmp(part2, "name", 4))
        {
            request->field = FIRST_NAME;

            // must be operator
            part3 = strtok(NULL, " ");
            set_operator(part3, request);

            part4 = strtok(NULL, " ");
            if (!part4)
            {
                print_func("you must enter an argument after operator", sock);
                return;
            }
            if (strlen(part4) > 49)
            {
                print_func("error argument to long !", sock);
                return;
            }

            part4[strlen(part4) - 1] = 0;

            strcpy(request->arg, part4);
        }
    }
    else if (!strncmp(part1, "second", 5))
    {
        part2 = strtok(NULL, " ");

        // not sure needed
        if (!part2)
        {
            print_func("error you should insert a space after second !", sock);
            request->field = UNKNOW_FIELD;
            return;
        }

        if (!strncmp(part2, "name", 4))
        {
            request->field = SECOND_NAME;

            // must be operator
            part3 = strtok(NULL, " ");
            set_operator(part3, request);

            part4 = strtok(NULL, " ");
            if (!part4)
            {
                print_func("you must enter an argument after operator", sock);
                return;
            }
            if (strlen(part4) > 49)
            {
                print_func("error argument to long !", sock);
                return;
            }

            part4[strlen(part4) - 1] = 0;
            strcpy(request->arg, part4);
        }
    }
    else if (!strncmp(part1, "id", 2))
    {
        // here we must check the id format
        request->field = ID;

        part2 = strtok(NULL, " ");
        set_operator(part2, request);

        part3 = strtok(NULL, " ");
        if (!part3)
        {
            print_func("you must enter an argument after operator !", sock);
            return;
        }

        // remove new line character
        part3[strlen(part3) - 1] = 0;

        if (strlen(part3) > 10)
        {
            print_func("error id len must be 10 !", sock);
            return;
        }

        if (!is_digit_str(part3))
        {
            print_func("error id must be only numbers !", sock);
            return;
        }

        strcpy(request->arg, part3);
    }
    else if (!strncmp(part1, "phone", 5))
    {
        // here we must check the phone format
        request->field = PHONE;

        part2 = strtok(NULL, " ");
        set_operator(part2, request);

        part3 = strtok(NULL, " ");
        if (!part3)
        {
            print_func("you must enter an argument after operator", sock);
            return;
        }

        // remove new line character
        part3[strlen(part3) - 1] = 0;

        if (strlen(part3) != 11)
        {
            print_func("error phone number must be 10 numbers !", sock);
            return;
        }
        if (!is_digit_str(part3))
        {
            print_func("error id must be only numbers !", sock);
            return;
        }

        strcpy(request->arg, part3);
    }
    else if (!strncmp(part1, "date", 4))
    {
        // here we must check the date format
        request->field = DATE;
        part2 = strtok(NULL, " ");
        set_operator(part2, request);

        part3 = strtok(NULL, " ");
        if (!part3)
        {
            print_func("you must enter an argument after operator", sock);
            return;
        }
        if (strlen(part3) != 11)
        {
            print_func("error date should be formated: dd/mm/yyyy", sock);
            return;
        }

        part3[strlen(part3) - 1] = 0;
        strcpy(request->arg, part3);
    }
    else if (!strncmp(part1, "debt", 4))
    {
        // here we must check the debt format
        request->field = DEBT;

        part2 = strtok(NULL, " ");
        set_operator(part2, request);

        part3 = strtok(NULL, " ");
        if (!part3)
        {
            print_func("you must enter an argument after operator", sock);
            return;
        }
        if (strlen(part3) > 10)
        {
            print_func("argument to long !", sock);
            return;
        }
        if (atoi(part3) == 0)
        {
            print_func("error you must enter a valid number", sock);
            return;
        }

        part3[strlen(part3) - 1] = 0;
        strcpy(request->arg, part3);
    }
    else
    {
        print_func("unknow field !", sock);
        request->field = UNKNOW_FIELD;
    }
}