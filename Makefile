CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LIBS = -lm
TARGET = points_distance
SOURCE = points_distance.c

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE) $(LIBS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run