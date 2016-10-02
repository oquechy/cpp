CC=gcc
CFLAGS=-c -Wall -I./include

TARGET=ms_cli
BIN=bin
_OBJ = mergesort.o $(TARGET).o 
OBJ = $(patsubst %,bin/%,$(_OBJ))

_DEPS = mergesort.h
DEPS = $(patsubst %,include/%,$(_DEPS))

ms_cli: bin $(OBJ) 
	$(CC) $(OBJ) -o $@

bin:
	mkdir -p $@

bin/%.o: src/%.c $(DEPS)    
	$(CC) $(CFLAGS) $< -o $@ 
                                        
.PHONY : clean

clean:
	rm -rf bin $(TARGET)
