#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "customer.h"
#include "vector_customer.h"

#define BUFFER_SIZE 256

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("please input file name !\n");
        return 1;
    }

    char * csv_file_path = argv[1];
    FILE * f = fopen(csv_file_path, "r");
    int line_number = 1;
    int read = 0;
    int records = 0;
    
    // test vector customer
    Vector_customer v;
    vector_init(&v);


    if (!f)
    {
        printf("error with reading <%s> file\n", csv_file_path);
    }

    char buffer[BUFFER_SIZE];

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
            //vector_add_by_value(&v, tmp);
            vector_add(&v, &tmp);
        }
        else
        {
            printf("line %d is bad formated in file: %s\n", line_number, csv_file_path);
            // add to error struct
        }
    }

    fclose(f);

    printf("we succesfull read %d records in file %s\n", records, csv_file_path);

    vector_print(&v);
    
    vector_free(&v);







    
    return 0;
}