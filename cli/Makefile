TARGET = $(shell uname)

EXT_DIR = ../fuior_compiler/native_extension
BIN_EXT =

SOURCES = \
	main.c \
	$(EXT_DIR)/include/tree_sitter/src/lib.c \
	$(EXT_DIR)/src/fuior.c \
	$(EXT_DIR)/include/parser.c

HEADERS = $(EXT_DIR)/src/fuior.h

INCLUDES = -I. -I$(EXT_DIR)/src -I$(EXT_DIR)/include
CFLAGS = -std=gnu11

build/$(TARGET)/fuior$(BIN_EXT): $(SOURCES) $(HEADERS)
	mkdir -p build/$(TARGET)
	$(CC) -o $@ $(SOURCES) $(CFLAGS) $(INCLUDES)
