CC = gcc
CFLAGS = -Wall -g -lm -pthread
EXEC = Main
DEPS = $(IDIR)LinkedList.h RTA.h
OBJ = main.o $(IDIR)LinkedList.o RTA.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

Main: $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^
