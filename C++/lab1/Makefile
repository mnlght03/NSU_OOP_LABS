CC = g++
CFLAGS = -Wall -Wextra

.PHONY: clean_o clean rebuild

all: Bigint clean_o

Bigint: Bigint_build main.cpp
	$(CC) $(CFLAGS) Bigint_assignment_and_increment_operators.o Bigint_bool_operators.o Bigint_cast_operators.o Bigint_constructors.o Bigint_math_operators.o Bigint_size_operators.o main.cpp -o main

Bigint_o: Bigint_build
	$(CC) $(CFLAGS) Bigint_assignment_and_increment_operators.o Bigint_bool_operators.o Bigint_cast_operators.o Bigint_constructors.o Bigint_math_operators.o Bigint_size_operators.o -o Bigint.o

Bigint_build: Bigint_assignment_and_increment_operators.cpp Bigint_bool_operators.cpp Bigint_cast_operators.cpp Bigint_constructors.cpp Bigint_math_operators.cpp Bigint_size_operators.cpp
	$(CC) -c Bigint_assignment_and_increment_operators.cpp Bigint_bool_operators.cpp Bigint_cast_operators.cpp Bigint_constructors.cpp Bigint_math_operators.cpp Bigint_size_operators.cpp

run_tests: Bigint_build
	$(CC) Bigint_tests.cpp Bigint_assignment_and_increment_operators.o Bigint_bool_operators.o Bigint_cast_operators.o Bigint_constructors.o Bigint_math_operators.o Bigint_size_operators.o /usr/local/lib/libgtest.a -lpthread -o Bigint_tests && ./Bigint_tests
	make clean_o

clean_o:
	rm -rf *.o Bigint_tests

clean:
	rm -rf *.o main

rebuild: clean all
