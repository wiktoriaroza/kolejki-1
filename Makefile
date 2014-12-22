CC=gcc
CFLAGS=-Wall -g
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))
LIBS=$(patsubst %, %.o, err)
BINS=serwer komisja raport

test : $(BINS)
	./serwer

$(BINS) : $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $@.o -o $@

%.o : %.c
	$(CC) $(CFLAGS) $< -c

clobber :
	rm -f $(OBJS)
	rm -f *.bak
	rm -f *.exe

.PHONY : test clobber
