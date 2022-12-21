CC = gcc
CFLAGS = -g -Wall 
EXE = runProj
HEADERS = stack.h tree.h types.h
CODE = proj4.c stack.c tree.c

OBJECTS = $(CODE:.c=.o)

lab9: $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXE)

clean:
	rm -f *.o *.exe *.out