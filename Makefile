IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=./obj

LIBS=-lpopt

_DEPS = sendmessage/sendmessage.h commandline/commandline.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = sendmessage.o commandline.o utils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: subdirs sendmsg 

sendmsg: $(OBJ)
	$(CC) server.c -o $@ $^ $(CFLAGS) $(LIBS)

exclude_dirs := include  bin  lib  test  obj
dirs:=$(shell find . -maxdepth 1 -type d)
dirs:=$(basename $(patsubst ./%,%,$(dirs)))
dirs:=$(filter-out $(exclude_dirs),$(dirs))
SUBDIRS := $(dirs)

subdirs:$(SUBDIRS)
	mkdir $(ODIR)
	for dir in $(SUBDIRS);\
	do cd $$dir && make && cd ../;\
	done

.PHONY: clean

clean:
	rm -fr $(ODIR)
