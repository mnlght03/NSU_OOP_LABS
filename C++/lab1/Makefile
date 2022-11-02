CC = g++
CFLAGS = -Wall -Wextra

.PHONY: clean_o clean rebuild

all: main clean_o

main: Bigint_lib main.cpp
	$(CC) $(CFLAGS) main.cpp Bigint.a -o main

Bigint_lib: Bigint_build
	ar rvs Bigint.a Bigint_assignment_and_increment_operators.o Bigint_bool_operators.o Bigint_cast_operators.o Bigint_constructors.o Bigint_math_operators.o Bigint_size_operators.o
	make clean_o

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
