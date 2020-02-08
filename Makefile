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

