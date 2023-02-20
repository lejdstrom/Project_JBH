#include "data_base.h"

Vector_customer *init_db(char path[] /* Vector_customer *v */)
{
    FILE *f = fopen(path, "r");
    int line_number = 1;
    int read = 0;
    int records = 0;
    char buffer[BUFFER_SIZE];

    // static vector
    Vector_customer *v = malloc(sizeof(Vector_customer));
    vector_init(v);

    if (!f)
    {
        printf("error with reading <%s> file\n", path);
    }

    // we skip the first line of our csv file
    fgets(buffer, sizeof(buffer), f);

    while (fgets(buffer, sizeof(buffer), f))
    {
        line_number++;
        Customer tmp = {};

        // we except 6 fields
        read = sscanf(buffer, "%49[^,],%49[^,],%9[0-9],%10[0-9],%10[^,],%10[^\n]",
                      tmp.first_name,
                      tmp.second_name,
                      tmp.id,
                      tmp.phone_number,
                      tmp.date,
                      tmp.debt);

        if (read == 6)
        {
            // add to db
            records++;
            vector_add(v, &tmp);
        }
        else
        {
            printf("line %d is bad formated in file: %s\n", line_number, path);
            // add to error struct
        }
    }

    fclose(f);

    return v;
}

void free_db(Vector_customer *v)
{
    vector_free(v);
    free(v);
}

// bubble sort improved
// best case O(n)
void sort(Vector_customer *vector)
{
    int len = vector->total;
    int swap = 0;
    Customer tmp_customer = {};

    for (int i = 0; i < len; i++)
    {
        swap = 0;
        for (int j = 0; j < len -1; j++)
        {
            if (atoi(vector->data[j].debt) > atoi(vector->data[j+1].debt))
            {
                tmp_customer = vector->data[j+1];
                vector->data[j+1] = vector->data[j];
                vector->data[j] = tmp_customer;
                
                swap = 1;
            }
            
        }
        if(!swap)
        {
            break;
        }
    }
}

// sort vector according to debt field
// and print
void print_db(Vector_customer *v)
{
    sort(v);
    vector_print(v);
}

void answer_request(Vector_customer *data_base, Vector_customer *out, cmp_func f, Select_request *request)
{
    for (int i = 0; i < data_base->total; i++)
    {
        if (f(&data_base->data[i], request->operator, request->arg))
        {
            add_customer_to_vector(out, &data_base->data[i]);
        }
    }
}

void add_customer_to_vector(Vector_customer *v, Customer *c)
{
    if (v->capacity == v->total)
    {
        vector_resize(v, v->capacity * 2);
    }

    v->data[v->total++] = *c;
}

Set_Insert_Db_Message add_customer_to_db(Vector_customer *v, Customer *c, char path[])
{

    // add in hard drive
    FILE *f = fopen(path, "a+");

    if (!f)
    {
        printf("error with reading <%s> file\n", path);
        return ERROR_WITH_FILE;
    }

    int index = index_of_id(v, c->id);

    if (index >= 0) // found in our data base
    {
        // check if fname and sname are the same
        if (strcmp(v->data[index].first_name, c->first_name) || strcmp(v->data[index].second_name, c->second_name))
        {
            return ID_ALREADY_EXIST_WITH_DIFF_NAME;
        }

        if (strcmp(v->data[index].phone_number, c->phone_number))
        {
            // update phone number
            snprintf(v->data[index].phone_number, PHONE_LEN + 1, "%s", c->phone_number);

            // we update the csv file for the next opening
            fprintf(f, "\n%s,%s,%s,%s,%s,%s",
                c->first_name,
                c->second_name,
                c->id,
                c->phone_number,
                c->date,
                // c->debt
                // we can only update one field each time !
                v->data[index].debt
                );

            fclose(f);

            return UPDATE_PHONE;
        }

        int old_debt = atoi(v->data[index].debt);
        int new_debt = atoi(c->debt);

        int result = old_debt + new_debt;

        if (result != old_debt)
        {
            snprintf(v->data[index].debt, MAX_DEBT_LEN, "%d", result);

            // we update the csv file for the next opening
            fprintf(f, "\n%s,%s,%s,%s,%s,%s",
                c->first_name,
                c->second_name,
                c->id,
                c->phone_number,
                c->date,
                c->debt);

            fclose(f);

            return UPDATE_DEBT;
        }
    }
    else // not found in db, so we must add it
    {

        fprintf(f, "\n%s,%s,%s,%s,%s,%s",
                c->first_name,
                c->second_name,
                c->id,
                c->phone_number,
                c->date,
                c->debt);

        fclose(f);

        // add in db (ram)
        add_customer_to_vector(v, c);

        return NEW_CUSTOMER;
    }

    // gcc -Wall warning :"control reaches end of non void function"
    // should not be reached
    return NO_ERROR;
}

void display_insert_db_message(Set_Insert_Db_Message message, Customer *customer)
{
    switch (message)
    {
    case ID_ALREADY_EXIST_WITH_DIFF_NAME:
        printf("the id: %s is already in data base with a different name !\n", customer->id);
        return;

    case UPDATE_PHONE:
        printf("the phone of %s %s was updated to: %s\n", customer->first_name, customer->second_name, customer->phone_number);
        return;

    case UPDATE_DEBT:
        printf("the debt of %s %s was updated\n", customer->first_name, customer->second_name);
        return;

    case NEW_CUSTOMER:
        printf("new customer ! %s %s was added to db\n", customer->first_name, customer->second_name);

    case ERROR_WITH_FILE:
        printf("problem with opening file\n");
    }
}

// char *string
int cmp_first_name(Customer *c, Operators op, char *arg)
{
   return cmp_string(c->first_name, arg, op);
}

int cmp_second_name(Customer *c, Operators op, char *arg)
{
    return cmp_string(c->second_name, arg, op);
}

int cmp_date(Customer *c, Operators op, char *arg)
{
    int day_c = atoi(c->date);
    int month_c = atoi(c->date + 3);
    int year_c = atoi(c->date + 6);

    int day = atoi(arg);
    int month = atoi(arg + 3);
    int year = atoi(arg + 6);

    int date1 = day_c + month_c * 30 + year_c * 360;
    int date2 = day + month * 30 + year * 360;

    return cmp_number(date1, date2, op);
}

int cmp_id(Customer *c, Operators op, char *arg)
{
    return cmp_string(c->id, arg, op);
}

int cmp_debt(Customer *c, Operators op, char *arg)
{
    int c_debt = atoi(c->debt);
    int arg_debt = atoi(arg);

    return cmp_number(c_debt, arg_debt, op);
}

int cmp_phone(Customer *c, Operators op, char *arg)
{
    return cmp_string(c->phone_number, arg, op);
}

int cmp_string(char *str1, char *str2, Operators operator)
{
    switch (operator)
    {
    case EQUAL:
        return (!strcmp(str1, str2));

    case NOT_EQUAL:
        return (strcmp(str1, str2));

    case GREATER:   
        return (strcmp(str1, str2) > 0);

    case SMALLER:
        return (strcmp(str1, str2) < 0);

    case UNKNOW_OP:
        return UNKNOW_OP;

    default:
        return NO_ERROR;
    }
}

int cmp_number(int num1, int num2, Operators operator)
{
    switch (operator)
    {
    case EQUAL:
        return (num1 == num2);

    case NOT_EQUAL:
        return (num1 != num2);

    case GREATER:
        return (num1 > num2);
            
    case SMALLER:
        return (num1 < num2);
    
    case UNKNOW_OP:
        return UNKNOW_OP;

    default:
        return NO_ERROR;
    }
}

cmp_func function_dispatcher(Select_request *request)
{
    switch (request->field)
    {
    case FIRST_NAME:
        return cmp_first_name;

    case SECOND_NAME:
        return cmp_second_name;

    case PHONE:
        return cmp_phone;

    case ID:
        return cmp_id;

    case DEBT:
        return cmp_debt;

    case DATE:
        return cmp_date;

    case UNKNOW_FIELD:
        return NULL;

    default:
        return NULL;
    }
}