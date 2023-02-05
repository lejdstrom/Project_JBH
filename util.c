#include "util.h"

Set_Errors parse_set(char set_command[], Customer *customer)
{
    int read = 0;
    //Customer tmp = {};

    // we except 6 fields
    read = sscanf(set_command, " first name=%49[^,], second name=%49[^,], id=%9[0-9], phone=%10[0-9], date=%10[^,], debt=%10[^\n]",
                  customer->first_name,
                  customer->second_name,
                  customer->id,
                  customer->phone_number,
                  customer->date,
                  customer->debt
                  );

    // big bug if read == 0 because FIRST_NAME == 0 !!!
    switch (read)
    {
    case 0:
        pust("problem with set command: 0 fields were read");
        return NO_FIELDS_READ;

    case FIRST_NAME:
        puts("we read only first name");
        return ERR_F_NAME;

    case SECOND_NAME:
        puts("we read until second name");
        return ERR_S_NAME;

    case ID:
        puts("we read until id");
        return ERR_ID;

    case PHONE:
        puts("we read until phone");
        return ERR_PHONE;
    
    case DATE:
        puts("we read until date");
        return ERR_DATE;

    case DEBT:
        puts("we read until debt");
        return ERR_DEBT;

    case NO_ERROR:
        puts("no error ! we read all the fields !");
        return NO_ERROR;
    }
}

Set_Errors_ID validate_ID(char id[])
{
    int id_len = strlen(id);

    if(!is_digit_str(id))
    {
        return ID_NOT_NUMBER;
    }

    if( id_len > 10 || id_len < 10 )
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

Customer_Fields_Errors validate_fields(Customer *customer)
{

    Customer_Fields_Errors tmp = {};

    tmp.date = validate_Date(customer->date);
    tmp.debt = validate_Debt(customer->debt);
    tmp.id = validate_ID(customer->id);
    tmp.phone = validate_Phone(customer->phone_number);

    if(tmp.date == DATE_NO_ERROR && tmp.debt == DEBT_NO_ERROR && tmp.id == ID_NO_ERROR && tmp.phone == PHONE_NO_ERROR)
    {
        tmp.no_error = 1;
    }
    else
    {
        tmp.no_error = 0;
    }
    
    return tmp;
}

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

void parse_set(char *arr, Set_request *set_request, Customer *tmp)
{
    /*
    part1 = strtok(NULL, ",\n");

    if (!strncmp(part1, fields[FIRST_NAME], 11))
    {
        // look for string after equal
        //should be first name
        fields_arg_ptr[FIRST_NAME] = part1 + 11;

        printf("here the string after equal: %s\n", fields_arg_ptr[FIRST_NAME]);

    }

    k=1;
    printf("%d word parsed: %s\n", k++, part1);

    while(part1)
    {
        part1 = strtok(NULL, ",\n");

        printf("%d word parsed: %s\n", k++, part1);
    }
    */
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

void parse_select(char *arr, Select_request *request)
{
    char *part1 = strtok(NULL, " ");
    char *part2 = NULL; // strtok(NULL /*+ strlen(part1)*/, " ");
    char *part3 = NULL;
    char *part4 = NULL;

    if (!part1)
    {
        puts("you must enter a field after select");
        request->field = UNKNOW_FIELD;
        return;
    }

    if (!strcmp(part1, "first"))
    {
        part2 = strtok(NULL, " ");

        // not sure needed
        if (!part2)
        {
            puts("error you should insert a space after first !");
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
                puts("you must enter an argument after operator");
                return;
            }
            if (strlen(part4) > 49)
            {
                puts("error argument to long !");
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
            puts("error you should insert a space after second !");
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
                puts("you must enter an argument after operator");
                return;
            }
            if (strlen(part4) > 49)
            {
                puts("error argument to long !");
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
            puts("you must enter an argument after operator !");
            return;
        }

        // remove new line character
        part3[strlen(part3) - 1] = 0;

        if (strlen(part3) > 10)
        {
            puts("error id len must be 10 !");
            return;
        }

        if (!is_digit_str(part3))
        {
            puts("error id must be only numbers !");
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
            puts("you must enter an argument after operator");
            return;
        }

        // remove new line character
        part3[strlen(part3) - 1] = 0;

        if (strlen(part3) != 11)
        {
            puts("error phone number must be 10 numbers !");
            return;
        }
        if (!is_digit_str(part3))
        {
            puts("error id must be only numbers !");
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
            puts("you must enter an argument after operator");
            return;
        }
        if (strlen(part3) != 11)
        {
            puts("error date should be formated: dd/mm/yyyy");
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
            puts("you must enter an argument after operator");
            return;
        }
        if (strlen(part3) > 10)
        {
            puts("argument to long !");
            return;
        }
        if (atoi(part3) == 0)
        {
            puts("error you must enter a valid number");
            return;
        }

        part3[strlen(part3) - 1] = 0;
        strcpy(request->arg, part3);
    }
    else
    {
        puts("unknow field !");
        request->field = UNKNOW_FIELD;
    }
}
