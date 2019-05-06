CC          = g++
CFLAGS      = -Wall -pedantic -g -Wextra -O2
DEBUGGER    = valgrind --leak-check=yes
SRC         = $(wildcard *.cc)

all: prog run clean

prog: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

run: prog
	$(DEBUGGER) ./prog $(ARG)

clean:
	rm -rf *o prog