# this make file has been done with the assistance of Chat GPT

CC = gcc
CFLAGS = -g

TARGET = main

# finds all .c files recursively and creates coresponding .o files
SRCS := $(shell find . -name "*.c")
OBJS := $(SRCS:.c=.o)

all: $(TARGET)

# links objects to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -lm 


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# removes all generated files
clean:
	rm -f $(OBJS) $(TARGET)


.PHONY: all clean