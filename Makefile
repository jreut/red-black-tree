CC = gcc
CFLAGS = -Wall -Wpedantic -g

EXE = set

all: compile

compile: set

set: set.c
	${CC} ${CFLAGS} -o $@ $^ ${LDFLAGS}

clean:
	rm -f ${EXE} *.o
