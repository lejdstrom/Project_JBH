#include "data_base.h"

Vector_customer *init_db(char path[])
{

    FILE *f = fopen(path, "r");
    int line_number = 1;
    int read = 0;
    int records = 0;
    char buffer[BUFFER_SIZE];

    // test vector customer
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
            // check if tmp.id already in db
            // if true then update customer.debt
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
void print_db(Vector_customer *v)
{
    // quick_sort(v->data, sizeof(Customer), 0, v->total, cmp_debt_sort);

    //merge_sort(v->data, 0, v->total);

    sort(v);
    vector_print(v);
}

// c1 and c2 are both customer struct
int cmp_debt_sort(void *c1, void *c2)
{
    Customer *_c1 = (Customer *)c1;
    Customer *_c2 = (Customer *)c2;

    int debt1 = atoi(_c1->debt);
    int debt2 = atoi(_c2->debt);

    return debt1 - debt2;
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
        return;
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
    }
}

int cmp_first_name(Customer *c, Operators op, char *arg)
{
    switch (op)
    {
    case EQUAL:
        return (!strcmp(c->first_name, arg));

    case NOT_EQUAL:
        return (strcmp(c->first_name, arg));

    case GREATER:
        return (strcmp(c->first_name, arg) > 0);

    case SMALLER:
        return (strcmp(c->first_name, arg) < 0);
    }
}

int cmp_second_name(Customer *c, Operators op, char *arg)
{
    switch (op)
    {
    case EQUAL:
        return (!strcmp(c->second_name, arg));

    case NOT_EQUAL:
        return (strcmp(c->second_name, arg));

    case GREATER:
        return (strcmp(c->second_name, arg) > 0);

    case SMALLER:
        return (strcmp(c->second_name, arg) < 0);
    }
}

int cmp_date(Customer *c, Operators op, char *arg)
{
    int day_c = atoi(c->date);
    int month_c = atoi(c->date + 3);
    int year_c = atoi(c->date + 6);

    int day = atoi(arg);
    int month = atoi(arg + 3);
    int year = atoi(arg + 6);


    switch (op)
    {
    case EQUAL:
        return (!strcmp(c->date, arg));

    case NOT_EQUAL:
        return (strcmp(c->date, arg));

    case GREATER:
        return cmp_date_helper(day_c, month_c, year_c, day, month, year);
            

    case SMALLER:
        return !cmp_date_helper(day_c, month_c, year_c, day, month, year);
    }
}


// return 1 if date_1 > date_2
int cmp_date_helper(int d1, int m1, int y1, int d2, int m2, int y2)
{
    if(y1 < y2)
    {
        return 0;
    }
    else if(y1 > y2)
    {
        return 1;
    }
    else if(y1 == y2)
    {
        if(m1 < m2)
        {
            return 0;
        }
        else if(m1 > m2)
        {
            return 1;
        }
        else if(m1 == m2)
        {
            if(d1 < d2)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
}

int cmp_id(Customer *c, Operators op, char *arg)
{
    switch (op)
    {
    case EQUAL:
        return (!strncmp(c->id, arg, 9));

    case NOT_EQUAL:
        return (strncmp(c->id, arg, 9));

    case GREATER:
        return (strncmp(c->id, arg, 9) > 0);

    case SMALLER:
        return (strncmp(c->id, arg, 9) < 0);
    }
}

int cmp_debt(Customer *c, Operators op, char *arg)
{
    int c_debt = atoi(c->debt);
    int arg_debt = atoi(arg);

    switch (op)
    {
    case EQUAL:
        return (c_debt == arg_debt);

    case NOT_EQUAL:
        return (c_debt != arg_debt);

    case GREATER:
        return (c_debt > arg_debt);

    case SMALLER:
        return (c_debt < arg_debt);
    }
}

int cmp_phone(Customer *c, Operators op, char *arg)
{
    switch (op)
    {
    case EQUAL:
        return !strncmp(c->phone_number, arg, 10);

    case NOT_EQUAL:
        return strncmp(c->phone_number, arg, 10);

    case GREATER:
        return (strncmp(c->phone_number, arg, 10) > 0);

    case SMALLER:
        return (strncmp(c->phone_number, arg, 10) < 0);
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
    }
}