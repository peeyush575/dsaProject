# Compiler
CC = gcc

# Source files
SRC = mst.c graph.c
# Executable name
TARGET = dynamicMST

# Default rule
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(SRC)
	$(CC) -o $@ $^

# Clean rule
clean:
	rm -f $(TARGET)
