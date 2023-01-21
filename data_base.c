#include "data_base.h"

Vector_customer * init_db(char path[])
{


    FILE * f = fopen(path, "r");
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

        // we except 8 fields
        read = sscanf(buffer, "%49[^,],%49[^,],%9[0-9],%10[0-9],%u/%u/%u,%10[^\n]",
        tmp.first_name,
        tmp.second_name,
        tmp.id,
        tmp.phone_number,
        &tmp.day,
        &tmp.month,
        &tmp.year,
        tmp.debt
        );

        if(read == 8)
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
    quick_sort(v->data, sizeof(Customer), 0, v->total, cmp_debt);
    vector_print(v);
}

// c1 and c2 are both customer struct
int cmp_debt(void *c1, void *c2)
{
    Customer *_c1 = (Customer *)c1;
    Customer *_c2 = (Customer *)c2;

    int debt1 = atoi(_c1->debt);
    int debt2 = atoi(_c2->debt);

    return debt1 - debt2;
}
