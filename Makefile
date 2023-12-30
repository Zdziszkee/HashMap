CC = g++
CFLAGS = -Wall -Wextra -O3 -pedantic -std=c++17

all: Dictionary.x

Dictionary.x: Dictionary.cpp
	$(CC) $(CFLAGS) -o Dict.x Dictionary.cpp
Dictionary:
	./Dict.x pairs.txt < input.txt > output.txt
	diff -s result.txt output.txt
clean:
	rm -f *.x