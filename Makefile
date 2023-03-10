main: customer.o vector_customer.o main_local.o data_base.o util.o
	gcc -Wall -g customer.o vector_customer.o main_local.o data_base.o util.o -o main

main_local.o: main_local.c data_base.h data_base.c
	gcc -Wall -c -g main_local.c data_base.c

customer.o: customer.c customer.h
	gcc -Wall -c -g customer.c

vector_customer.o: vector_customer.h vector_customer.c
	gcc -Wall -c -g vector_customer.c

data_base.o: data_base.h data_base.c util.h util.c
	gcc -Wall -c -g data_base.c util.c

util.o : util.h util.c
	gcc -Wall -c -g util.c

test_memory:
	valgrind ./main data.csv --track-origin=yes -leak--check=full

debug:
	gdb --args ./main data.csv

clean:
	@rm -f *.o main