CC=gcc
CFLAGS=-Wall -Wextra -std=c99
LIBDIR=./lib

default: parser

parser: parser.c vector.o
	$(CC) $(CFLAGS) -o $@ $< -I$(LIBDIR) $(LIBDIR)/vector.o

vector.o:
	$(CC) $(CFLAGS) -c $(LIBDIR)/vector.c -o $(LIBDIR)/$@

run: test_file.c parser 
	./parser $<
