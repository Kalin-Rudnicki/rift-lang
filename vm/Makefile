
CC = gcc
CFLAGS = 

# Test Drivers
test: test.o
	$(CC)\
		out/test.o\
		-o bin/test\
		$(CFLAGS)

# Object Files

VmException.o: src/lib/VmException.c src/lib/VmException.c
	$(CC) -c src/lib/VmException.c -o out/VmException.o $(CFLAGS)

String.o: src/lib/String.c src/lib/String.h VmException.o
	$(CC) -c src/lib/String.c -o out/String.o $(CFLAGS)

test.o: test/test.c
	$(CC) -c test/test.c -o out/test.o $(CFLAGS)
