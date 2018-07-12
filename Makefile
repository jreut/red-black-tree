CC = gcc
CFLAGS = -Wall -Wpedantic -g

all: compile

compile: set

set: set.c
	${CC} ${CFLAGS} -o $@ $^ ${LDFLAGS}
