# Compilers and options
CC=gcc
CPPFLAGS= -MMD
CFLAGS= -Wall -Wextra -std=c99 -pedantic -O2 -g
LDFLAGS=
LDLIBS=
 
SRC = warmup.c
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
 
all: warmup
 
warmup: ${OBJ}
 
-include ${DEP}
 
clean:
	rm -f ${OBJ} ${DEP}
	rm -f main
 
# END
