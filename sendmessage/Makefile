IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=../obj

_DEPS = sendmessage/sendmessage.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = sendmessage.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c $< -o $@ $(CFLAGS)

sendmessage: $(OBJ)
	$(CC) -c -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(OBJ)
