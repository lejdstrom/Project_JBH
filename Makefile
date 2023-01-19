main: customer.o vector_customer.o main_local.o
	gcc -Wall -g customer.o vector_customer.o main_local.o -o main

customer.o: customer.c customer.h
	gcc -Wall -c -g customer.c

vector_customer.o: vector_customer.h vector_customer.c
	gcc -Wall -c -g vector_customer.c

test_memory:
	valgrind ./main data.csv --track-origin=yes -leak--check=full

clean:
	@rm -f *.o main