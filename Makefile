C = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
TARGET = my_ls

SRCS = src/main.c src/options.c src/display.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)

.PHONY: all clean
