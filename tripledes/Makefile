IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=../obj

LIBS=-lcrypto

_DEPS = tripledes/tripledes.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = tripledes.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

tripledes: $(OBJ)
	$(CC) -c -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJ)
