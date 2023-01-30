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

// sort vector according to debt field
void print_db(Vector_customer *v)
{
    quick_sort(v->data, sizeof(Customer), 0, v->total, cmp_debt_sort);
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
            add_db(out, &data_base->data[i]);
        }
    }
}

void add_db(Vector_customer *v, Customer *c)
{
    if (v->capacity == v->total)
    {
        vector_resize(v, v->capacity * 2);
    }

    v->data[v->total++] = *c;
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

/*int cmp_date(Customer *c, Operators op, char *arg)
{
    switch (op)
    {
    case EQUAL:
        return (!strcmp(c-, arg));

    case NOT_EQUAL:
        return;

    case GREATER:
        return;

    case SMALLER:
        return;
    }
}
*/

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

        // case DATE:
        //  return cmp_date;
    }
}