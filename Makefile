IDIR =./inc
CC=gcc
CFLAGS=-I$(IDIR) -std=c99 -pedantic-errors

ODIR =./obj
LDIR =./lib
SDIR =./src
BDIR =./bin

LIBS =-lm

_DEPS = mls.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = test.o mls.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

#./obj/test.o: ./src/test.c $(DEPS)
#	$(CC) -c -o ./obj/test.o ./src/test.c $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mlstest: $(OBJ)
	$(CC) -o $(BDIR)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ $(BDIR)/mlstest

