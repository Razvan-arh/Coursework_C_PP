CC = gcc
CFLAGS = -g

# Name of the executable
TARGET = square

# Automatically find all .c files recursively
SRCS := $(shell find . -name "*.c")
# Create corresponding object files (.o)
OBJS := $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

# Pattern rule: compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove all generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Optional: declare phony targets so Make won't confuse them with files
.PHONY: all clean