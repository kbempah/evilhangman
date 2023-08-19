CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS = main.o my_string.o generic_vector.o

all : string_driver

string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)
unit_test: my_string.o unit_test.o test_def.o
	$(CC) $(CFLAGS) -o unit_test unit_test.o test_def.o my_string.o
main.o: main.c my_string.h Status.h generic_vector.h
	$(CC) $(CFLAGS) -c main.c -o main.o
my_string.o: my_string.c my_string.h Status.h
	$(CC) $(CFLAGS) -c my_string.c -o my_string.o
unit_test.o: unit_test.c unit_test.h Status.h
	$(CC) $(CFLAGS) -c unit_test.c -o unit_test.o
test_def.o: test_def.c unit_test.h Status.h
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o
generic_vector.o : generic_vector.c generic.h generic_vector.h
	$(CC) $(CFLAGS) -c generic_vector.c -o generic_vector.o
.PHONY : clean
clean:
	-rm string_driver $(OBJECTS) unit_test unit_test.o test_def.o
