(CC) = g++
(CFLAGS) = -Wall -Wextra -Werror

all: BigInt main.cpp
	$(CC) $(CFLAGS) BigInt.o main.cpp -o main

BigInt: BigInt.cpp
	$(CC) $(CFLAGS) -c BigInt.cpp

clean:
	rm -rf *.o

rebuild: clean all
