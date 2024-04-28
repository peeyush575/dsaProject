# Compiler
CC = gcc
# Compiler flags
CFLAGS = -w

# Source files
SRC = mst.c graph.c
# Executable name
TARGET = dynamicMST

# Default rule
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

# Clean rule
clean:
	rm -f $(TARGET)