# Name: Makefile
# Description: Builds ./bin/polytest, to test the polyfit() function.
# Test Environment: Ubuntu 18.04.4 LTS, GNU Make 4.1, gcc version 7.4.0.
# Author: Henry M. Forson, Melbourne, Florida USA
#
# Synopsis:
#	make clean		-- removes old build files from the repo.
#	make			-- builds the ./bin/polytest executable.
#	./bin/polytest	-- runs the executable.
#
# Results:
#   $ make clean
#   rm -f ./obj/*.o *~ core /*~ ./bin/polytest
#   $ make
#   mkdir -p ./obj
#   mkdir -p ./bin
#   gcc -c -o obj/test.o src/test.c -I./inc -std=c99 -pedantic-errors -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -Wall -Wextra -Wpedantic
#   gcc -c -o obj/polyfit.o src/polyfit.c -I./inc -std=c99 -pedantic-errors -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -Wall -Wextra -Wpedantic
#   gcc -o ./bin/polytest obj/test.o obj/polyfit.o -I./inc -std=c99 -pedantic-errors -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -Wall -Wextra -Wpedantic -lm
#   $ ./bin/polytest 
#   Test 1 expected (-3.000000 * x) + 5.000000
#   Test 1 produced (-3.000000 * x) + 5.000000
#   Test 1 passed OK.

#   Test 2 expected (-0.142857 * x^2) + 0.485714
#   Test 2 produced (-0.142857 * x^2) + 0.485714
#   Test 2 passed OK.

#   Test 3 expected error = -4
#   Test 3 produced error = -4
#   Test 3 passed OK.

#   Test 4 expected (1.518293 * x) + 0.304878
#   Test 4 produced (1.518293 * x) + 0.304878
#   Test 4 passed OK.

#   Tests complete: 4 passed, 0 failed.


#------------------------------------------------------------------------------------
# MIT License
#
# Copyright (c) 2020 Henry M. Forson
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#------------------------------------------------------------------------------------


IDIR =./inc
CC=gcc
CFLAGS=-I$(IDIR) -std=c99 -pedantic-errors -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -Wall -Wextra -Wpedantic

ODIR =./obj
LDIR =./lib
SDIR =./src
BDIR =./bin

LIBS =-lm

_DEPS = polyfit.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = test.o polyfit.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

#./obj/test.o: ./src/test.c $(DEPS)
#	$(CC) -c -o ./obj/test.o ./src/test.c $(CFLAGS)

all: dirs polytest

dirs:
	mkdir -p $(ODIR)
	mkdir -p $(BDIR)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

polytest: $(OBJ)
	$(CC) -o $(BDIR)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(BDIR)/polytest

