# Makefile

CC=gcc
CPPFLAGS= -MMD -D_XOPEN_SOURCE=500
CFLAGS= -Wall -Wextra -std=c99 -O0 -g
LDFLAGS=
LDLIBS= -lprocps

SRC= process.c dot_out.c dotpstree.c
OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}

all: dotpstree

dotpstree: ${OBJ}

clean:
	${RM} ${OBJ}
	${RM} ${DEP}
	${RM} dotpstree

-include ${DEP}

# END
