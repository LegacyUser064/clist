# Global variables
CC=gcc
CFLAGS=-O2 -Wall -Wextra -g
CPPFLAGS=-I include

# Makefile specific variables
src_dir:=src
include_dir:=include
bin_dir:=bin
lib_dir:=lib

shared_lib_target:=$(lib_dir)/liblist.so
static_lib_target:=$(lib_dir)/liblist.a
test_target:=$(bin_dir)/test

# Setup searchpath
vpath %.c $(src_dir)
vpath %.h $(include_dir)

.SUFFIXES:
.PHONY: all shared static test clean distclean

all: shared static
shared: $(shared_lib_target)
static: $(static_lib_target)
test: $(test_target)

$(shared_lib_target): list.o
	$(CC) -shared -o $@ $^

$(static_lib_target): list.o
	ar rcs $@ $^

$(test_target): test.o $(static_lib_target)
	$(CC) -o $@ -L $(lib_dir) -l list $^

test.o: test.c list.h
list.o: list.c list.h

clean:
	rm -f *.o

distclean:
	rm -f *.o $(shared_lib_target) $(static_lib_target) $(test_target)

# Patterns
%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

# Create needed subdirectories if they are not present
$(shell mkdir -p $(bin_dir) $(lib_dir))
