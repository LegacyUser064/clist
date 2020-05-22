//brad With a small project like this, it would be a good opportunity
// to learn how to generate and rely on dependencies. If you setup your
// dependencies properly, you'll only ever need to compile things that
// have changed since the last compile. You can read about dependencies
// in the makefile book.
// Note: Very few people really understand dependencies, but it can save
// you a lot of time for a bigger project where you're compiling over and
// over. Having to recompile everything every time ends up wasting a surprising
// amount of time over the course of a project.
# Global variables
CC=gcc
CFLAGS=-O2 -Wall -Wextra -g
CPPFLAGS=-I include

# Makefile specific variables
//brad Would look better with some spaces:
// src_dir     := src
// include_dir := include
// bin_dir     := bin
// lib_dir     := lib

src_dir:=src
include_dir:=include
bin_dir:=bin
lib_dir:=lib

//brad Adding whitespace would aid readability
shared_lib_target:=$(lib_dir)/liblist.so
static_lib_target:=$(lib_dir)/liblist.a
test_target:=$(bin_dir)/test

# Setup searchpath
vpath %.c $(src_dir)
vpath %.h $(include_dir)

//brad You can delete .SUFFIXES. That's an old way of doing what vpath and
// pattern rules (e.g: "%.o: %.c") do now.
.SUFFIXES:

//brad Should all these targets be PHONY? PHONY says to make that a target
// should always be considered out of date.
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
