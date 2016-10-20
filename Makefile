#David Mayes
#150012384
#AC21008

CC=gcc
CFLAGS=-g -c -Wall -Wextra -pedantic
OBJECTS=cell.o
EXECUTABLE=cell


$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS)

cell.o: cell.h cell.c
	$(CC) $(CFLAGS) cell.c

.PHONY: clean
clean: 
	-rm -f $(EXECUTABLE) $(OBJECTS)
