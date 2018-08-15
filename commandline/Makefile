IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=../obj

LIBS=-lpopt

_DEPS = commandline/commandline.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = commandline.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

commandline: $(OBJ)
	$(CC) -c -o $@ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJ)
