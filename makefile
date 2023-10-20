CC = gcc
SOURCE = src/rio.c
TARGET = out/rio.o
CFLAGS = -c -g -Wall -o $(TARGET)

out/rio.o: $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE)

clean:
	$(RM) $(TARGET)
