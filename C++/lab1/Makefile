CC = g++
CFLAGS = -Wall -Wextra

all: BigInt main.cpp
	$(CC) $(CFLAGS) BigInt.o main.cpp -o main

run_tests: BigInt
	$(CC) BigInt_tests.cpp BigInt.o /usr/local/lib/libgtest.a -lpthread -o BigInt_tests && ./BigInt_tests

BigInt: BigInt.cpp
	$(CC) -c BigInt.cpp

clean:
	rm -rf *.o

rebuild: clean all
