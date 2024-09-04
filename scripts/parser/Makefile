CC=gcc
CFLAGS=-Wall -Wextra -std=c99

default: parser

parser: parser.c
	$(CC) $(CFLAGS) -o $@ $<

run: test_file.c parser 
	./parser $<
