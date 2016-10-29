#David Mayes
#150012384
#AC21008

CC=gcc
CFLAGS=-g -c -Wall -Wextra -pedantic
OBJECTS=cell.o conway.o CATester.o
EXECUTABLE=CATester


$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS)

cell.o: cell.h cell.c
	$(CC) $(CFLAGS) cell.c
	
conway.o: conway.c conway.h
	$(CC) $(CFLAGS) conway.c
	
CATester.o: CATester.c
	$(CC) $(CFLAGS) CATester.c

.PHONY: clean
clean: 
	-rm -f $(EXECUTABLE) $(OBJECTS)
