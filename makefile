CC = gcc
CFLAGS = -c -g -Wall -o out/rio.o

rio.o: src/rio.c
	$(CC) $(CFLAGS) src/rio.c

clean:
	$(RM) $(TARGET)
