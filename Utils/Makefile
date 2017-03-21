CC = gcc
CFLAGS = -Wall
DEPS = DoublyLinkedList.h
OBJ = DLL_main.o DoublyLinkedList.o

%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

DoublyLinkedList: $(OBJ)
		gcc $(CFLAGS) -o $@ $^
