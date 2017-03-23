IDIR = ../Utils/
CC = gcc
CFLAGS = -Wall -g -lm
EXEC = Main
DEPS = $(IDIR)LinkedList.h RTA.h
OBJ = main.o $(IDIR)LinkedList.o RTA.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

Main: $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^
