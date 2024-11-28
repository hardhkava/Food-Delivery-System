# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Executable target
TARGET = main

# Source files
SRCS = main.c admin_ui.c customerUI.c delivery.c restaurantUI.c

# Object files (replace .c with .o in SRCS)
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = admin_func.c center_logo.c customerfuncs.h restaurantfuncs.h welcome.c customers.txt deliveryworkers.txt restaurants.txt orders.txt completed.txt

# Default target: build the executable
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up generated files
.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
