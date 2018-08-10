IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=./obj

LIBS=-lpopt

_DEPS = sendmessage/sendmessage.h commandline/commandline.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = sendmessage.o commandline.o utils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

sendmessage: $(OBJ)
	$(CC) server.c -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJ)
