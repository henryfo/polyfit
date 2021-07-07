# Name: Makefile
# Description: Builds ./bin/test, to test the polyfit() function.
# Test Environment: Ubuntu 18.04.4 LTS, GNU Make 4.1, gcc version 7.4.0.
# Author: Henry M. Forson, Melbourne, Florida USA
# Modified by: Stephen P. Morgan, San Jose, California USA
#
# Synopsis:
#	make clean			-- removes old build files from the repo.
#	make				-- builds the ./bin/test-[1-3] executables.
#	./bin/test-1	-- runs the test-1 executable.
#	./bin/test-2	-- runs the test-2 executable.
#	./bin/test-3	-- runs the test-3 executable.
#	make test			-- build and runs all the test-[1-3] executables
#
# Results:
#   $ make clean
#	rm -f ./obj/*.o *~ core /*~ | true
#	rm -f ./bin/test-1 | true
#	rm -f ./bin/test-2 | true
#	rm -f ./bin/test-3 | true
#	
#   $ make
#	gcc -c -o obj/test-1.o src/test-1.c -I./inc -std=c99 -pedantic-errors -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -Wall -Wextra -Wpedantic -Werror
#	gcc -c -o obj/polyfit.o src/polyfit.c -I./inc -std=c99 -pedantic-errors -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -Wall -Wextra -Wpedantic -Werror
#	gcc -o bin/test-1 obj/test-1.o obj/polyfit.o -I./inc -std=c99 -pedantic-errors -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -Wall -Wextra -Wpedantic -Werror -lm
#	gcc -c -o obj/test-2.o src/test-2.c -I./inc -std=c99 -pedantic-errors -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -Wall -Wextra -Wpedantic -Werror
#	gcc -o bin/test-2 obj/test-2.o obj/polyfit.o -I./inc -std=c99 -pedantic-errors -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -Wall -Wextra -Wpedantic -Werror -lm
#	gcc -c -o obj/test-3.o src/test-3.c -I./inc -std=c99 -pedantic-errors -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -Wall -Wextra -Wpedantic -Werror
#	gcc -o bin/test-3 obj/test-3.o obj/polyfit.o -I./inc -std=c99 -pedantic-errors -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -Wall -Wextra -Wpedantic -Werror -lm
#	
#   $ ./bin/test-1
#	Test 1 expected (-3 * x) + 5
#	Test 1 produced (-3 * x) + 5
#	Test 1 passed OK.
#	
#	Test 2 expected (-0.142857142857 * x^2) + 0.485714285714
#	Test 2 produced (-0.142857142857 * x^2) + 0.485714285714
#	Test 2 passed OK.
#	
#	Test 3 expected error = -4
#	Test 3 produced error = -4
#	Test 3 passed OK.
#	
#	Test 4 expected (1.51829268293 * x) + 0.30487804878
#	Test 4 produced (1.51829268293 * x) + 0.30487804878
#	Test 4 passed OK.
#	
#	Tests complete: 4 passed, 0 failed.
#	
#   $ ./bin/test-2
#	Test: Polynomial Order 0:
#	Test produced 0.257133485183
#	Error was 0.573962.
#	-------------------
#	Test: Polynomial Order 2:
#	Test produced (-1.79342717745e-08 * x^2) + (9.56639730699e-06 * x) + 0.259546158319
#	Error was 0.057347; error improvement: total  90.009%, step  90.009%.
#	-------------------
#	Test: Polynomial Order 4:
#	Test produced (-5.22695213715e-14 * x^4) + (1.69607359765e-10 * x^3) + (-1.96715727627e-07 * x^2) + (7.83400126084e-05 * x) + 0.252368435981
#	Error was 0.016800; error improvement: total  97.073%, step  70.705%.
#	-------------------
#	Test: Polynomial Order 6:
#	Test produced (-6.10473179655e-19 * x^6) + (2.37734934503e-15 * x^5) + (-3.64187375235e-12 * x^4) + (2.80444481787e-09 * x^3) + (-1.15841078401e-06 * x^2) + (0.00023620315162 * x) + 0.243908991045
#	Error was 0.010339; error improvement: total  98.199%, step  38.456%.
#	-------------------
#	Test: Polynomial Order 8:
#	Test produced (-5.74676299091e-25 * x^8) + (3.10128708978e-21 * x^7) + (-7.5169670753e-18 * x^6) + (1.05850700619e-14 * x^5) + (-9.2593742705e-12 * x^4) + (5.03106050983e-09 * x^3) + (-1.64535953891e-06 * x^2) + (0.000288160416527 * x) + 0.241921948336
#	Error was 0.010258; error improvement: total  98.213%, step   0.780%.
#	
#	The order 6 polynomial is the best fit.
#	
#   $ ./bin/test-3
#	Searching for the optimal number of threads for a system with 56 CPUs.
#	
#	Test: Polynomial Order 6:
#	
#	(-6.10473179655e-19 * x^6) + (2.37734934503e-15 * x^5) + (-3.64187375235e-12 * x^4) + (2.80444481787e-09 * x^3) + (-1.15841078401e-06 * x^2) + (0.00023620315162 * x) + 0.243908991045
#	
#	The overall fitting error for that polynomial is 0.010339.
#	
#	Searching for roots of the derivative of that polynomial (for local maxima and minima).
#	
#	The derivative of that polynomial is (-3.66283907793e-18 * x^5) + (1.18867467252e-14 * x^4) + (-1.45674950094e-11 * x^3) + (8.41333445362e-09 * x^2) + (-2.31682156803e-06 * x) + 0.00023620315162
#	
#	polyRoot returned 964 (iterations 1, epsilon 0).
#	
#	polyEvaluate(964) returned 0.251574.
#	
#	The optimal number of threads (by CPUs) is 4xCPUs, or 224 (value 0.262309).
#	
#	The optimal number of threads (individually) is 240 (value 0.262335), or about 4.3xCPUs.
#	
#	Root 964 is a local minimum.

#------------------------------------------------------------------------------------
# MIT License
#
# Copyright (c) 2020 Henry M. Forson
# Copyright (c) 2021 Stephen P. Morgan
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

default: all

IDIR =./inc
ODIR =./obj
LDIR =./lib
SDIR =./src
BDIR =./bin

CC=gcc
CFLAGS=-I$(IDIR) -std=c99 -pedantic-errors -fsanitize=address -fno-omit-frame-pointer -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -Wall -Wextra -Wpedantic -Werror

LIBS =-lm

_TEST-1-DEPS = polyfit.h
TEST-1-DEPS = $(patsubst %,$(IDIR)/%,$(_TEST-1-DEPS))

_TEST-1-OBJ = test-1.o polyfit.o
TEST-1-OBJ = $(patsubst %,$(ODIR)/%,$(_TEST-1-OBJ))

$(BDIR)/test-1: $(TEST-1-OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

_TEST-2-DEPS = polyfit.h test-2-x.h test-2-y.h
TEST-2-DEPS = $(DEPS) + $(patsubst %,$(IDIR)/%,$(_TEST-2-DEPS))

_TEST-2-OBJ = test-2.o polyfit.o
TEST-2-OBJ = $(patsubst %,$(ODIR)/%,$(_TEST-2-OBJ))

$(BDIR)/test-2: $(TEST-2-OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

_TEST-3-DEPS = polyfit.h test-3-x.h test-3-y.h
TEST-3-DEPS = $(DEPS) + $(patsubst %,$(IDIR)/%,$(_TEST-3-DEPS))

_TEST-3-OBJ = test-3.o polyfit.o
TEST-3-OBJ = $(patsubst %,$(ODIR)/%,$(_TEST-3-OBJ))

$(BDIR)/test-3: $(TEST-3-OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: all clean dirs tar tarnogit test test-1 test-2 test-3

all: test-1 test-2 test-3

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ *.html | true
	rm -f $(BDIR)/test-1 | true
	rm -f $(BDIR)/test-2 | true
	rm -f $(BDIR)/test-3 | true
	@if [ -d ${ODIR} ] ; then \
		rmdir --ignore-fail-on-non-empty $(ODIR) ; \
	fi
	@if [ -d ${BDIR} ] ; then \
		rmdir --ignore-fail-on-non-empty $(BDIR) ; \
	fi

dirs:
	@if [ ! -d ${ODIR} ] ; then \
		mkdir -p $(ODIR) ; \
	fi
	@if [ ! -d ${BDIR} ] ; then \
		mkdir -p $(BDIR) ; \
	fi

tar: clean
	tar czvpf ../polyfit.tgz .

tarnogit: clean
	tar czvpf ../polyfit.tgz --exclude=.git .


test: all
	$(BDIR)/test-1
	$(BDIR)/test-2
	$(BDIR)/test-3

test-1: dirs $(BDIR)/test-1

test-2: dirs $(BDIR)/test-2

test-3: dirs $(BDIR)/test-3

