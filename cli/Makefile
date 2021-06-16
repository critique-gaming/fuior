TARGET = $(shell uname)

EXT_DIR = ../fuior_compiler/native_extension
BIN_EXT =

SOURCES = \
	main.c \
	$(EXT_DIR)/include/tree_sitter/src/lib.c \
	$(EXT_DIR)/include/parser.c \
	$(EXT_DIR)/src/fuior.c \
	$(EXT_DIR)/src/fuior_generate_lua.c \
	$(EXT_DIR)/src/fuior_analyze.c \
	$(EXT_DIR)/src/fuior_lint.c

HEADERS = \
	$(EXT_DIR)/include/fuior.h \
	$(EXT_DIR)/src/fuior_private.h \
	$(EXT_DIR)/src/fuior_strlist.h \
	$(EXT_DIR)/src/fuior_list.h \
	$(EXT_DIR)/src/fuior_map.h

INCLUDES = -I. -I$(EXT_DIR)/include
CFLAGS = -std=gnu11

build/$(TARGET)/fuior$(BIN_EXT): $(SOURCES) $(HEADERS)
	mkdir -p build/$(TARGET)
	$(CC) -o $@ $(SOURCES) $(CFLAGS) $(INCLUDES)

clean:
	rm -f build/$(TARGET)/fuior$(BIN_EXT)

.PHONY: clean
