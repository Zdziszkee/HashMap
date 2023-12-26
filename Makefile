CC = g++
CFLAGS = -Wall -Wextra -O3 -pedantic -std=c++17

all: Dictionary.x

Dictionary.x: Dictionary.cpp
	$(CC) $(CFLAGS) -o Dictionary.x Dictionary.cpp
clean:
	rm -f *.x