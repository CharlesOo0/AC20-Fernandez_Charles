CC=gcc
CFLAGS=-Wall -O2
LDFLAGS=
TARGET=main_list

all: main_list

main_list: main_list.c liste.h liste.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

