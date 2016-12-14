CC=gcc
CFLAGS=-c -g -Wall -I./include -std=c99 -Wall -Werror

TARGET=main

_OBJ = bmp.o $(TARGET).o
OBJ = $(patsubst %,bin/%,$(_OBJ))

_DEPS = bmp.h
DEPS = $(patsubst %,include/%,$(_DEPS))

$(TARGET): bin $(OBJ)
	$(CC) $(OBJ) -o $@

bin:
	mkdir -p $@

bin/%.o: src/%.c $(DEPS)
	$(CC) $(CFLAGS) $< -o $@

.PHONY : clean

clean:
	rm -rf bin $(TARGET)
