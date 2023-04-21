PROG = collatz
all: $(PROG)

# object files
HEAD =
OBJ = collatz.o

# libraries
LIB =
LIBFLAGS =

# compiler
CC	= gcc
DEBUG	= -ggdb
CSTD	=
WARN	= -Wall -Wextra -Werror
CDEFS	=
CFLAGS	= -I. $(DEBUG) $(WARN) $(CSTD) $(CDEFS)

$(OBJ):
collatz.o : collatz.c

# how to compile the target
$(PROG):	$(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFLAGS) -o $@

.phony: clean

clean:
	rm -f $(PROG) $(OBJ)
