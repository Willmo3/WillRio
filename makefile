CC = gcc
EXT = .o
CFLAGS = -c -g -Wall

TARGET = rio

$(TARGET):$(TARGET)$(EXT)
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET)$(EXT)

clean:
	$(RM) $(TARGET)
