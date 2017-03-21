CC = gcc
CFLAGS = -Wall -lm
DEPS = RTA.h
OBJ = main.o RTA.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

RTA: $(OBJ)
		gcc $(CFLAGS) -o $@ $^
