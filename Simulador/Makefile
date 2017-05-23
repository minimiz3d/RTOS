# Include directory (header files)
IDIR = ./Utils/
ACCDIR = $(IDIR)Accelerometer/
VISDIR = $(IDIR)Vision/

# Dependencies (from Utils folder)
DEPS = $(IDIR)GenericUtils.h $(ACCDIR)Accelerometer.h $(VISDIR)Vision.h

CC = gcc
CFLAGS = -Wall -g -lm -lpthread
EXEC = Main
OBJ = main.o $(IDIR)GenericUtils.o $(ACCDIR)Accelerometer.o $(VISDIR)Vision.o

# Object files
%.o: %.c $(DEPS)
		$(CC) $(CFLAGS) -c -o $@ $<

# Executable file
Main: $(OBJ)
		$(CC) $(CFLAGS) -o $@ $^
