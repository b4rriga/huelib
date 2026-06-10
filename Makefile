CC := gcc
CFLAGS := -Wall -Wextra -Wpedantic -Werror -std=c11 -O3 -lm

PREFIX ?= /usr/local
INCLUDEDIR := $(PREFIX)/include
LIBDIR := $(PREFIX)/lib

NAME := huelib
LIB := lib$(NAME).a
SRC := huelib.c
OBJ := huelib.o

all: $(LIB)

$(OBJ): $(SRC) huelib.h
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)

install: $(LIB)
	install -d $(INCLUDEDIR)
	install -d $(LIBDIR)
	install -m 644 huelib.h $(INCLUDEDIR)/
	install -m 644 $(LIB) $(LIBDIR)/
	$(MAKE) clean

uninstall:
	rm -f $(INCLUDEDIR)/huelib.h
	rm -f $(LIBDIR)/$(LIB)

clean:
	rm -f $(OBJ) $(LIB)

.PHONY: all install uninstall clean
