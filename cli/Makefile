SOURCES = \
	main.c \
	../include/tree_sitter/src/lib.c \
	../src/fuior.c \
	../include/parser.c

HEADERS = ../src/fuior.h

CFLAGS = -I. -I../src -I../include -g

build/fuior: $(SOURCES) $(HEADERS)
	$(CC) -o $@ $(SOURCES) $(CFLAGS)
