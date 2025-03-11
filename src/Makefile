CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

# Detect OS
UNAME_S := $(shell uname -s)

# macOS specific flags
ifeq ($(UNAME_S),Darwin)
    CFLAGS += -I/opt/homebrew/include
    LDFLAGS = -L/opt/homebrew/lib -lraylib -framework OpenGL -framework IOKit -framework Cocoa
endif

# Linux specific flags
ifeq ($(UNAME_S),Linux)
    LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

# Source files
SRCS = main.c \
       display/raylib_display.c \
       include/globals.c \
       include/maze.c \
       input/input.c \
       logic/game_logic.c \
       screens/screens.c \
       include/notconio.c

# Object files
OBJS = $(SRCS:.c=.o)

# Target
TARGET = retro-c-raylib
BINDIR = ../bin

# Default target
all: $(TARGET) install

# Link the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Install the executable to the bin directory
install: $(TARGET)
	mkdir -p $(BINDIR)
	cp $(TARGET) $(BINDIR)/

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(TARGET) $(BINDIR)/$(TARGET)

.PHONY: all clean install 