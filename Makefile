CC=gcc
CFLAGS=-Wall -Wextra -Werror

wc: main.o file.o
	$(CC) $^ -o $@

main.o: main.c file.h

file.o: file.c
