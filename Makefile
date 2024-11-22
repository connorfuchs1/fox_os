#Compiler and Flags
CC = gcc
CFLAGS=-I.

#Header deps
DEPS = fox_os.h

#Sources and Objects
SOURCES = fox_os.c
OBJECTS = $(SOURCES:.c=.o)

#Generated binaries
BINARIES = fox_os

all: fox_os

fox_os: fox_os.o 
	$(CC) -o fox_os fox_os.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJECTS) $(BINARIES)
