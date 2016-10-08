CC=gcc
CFLAGS=-c -Wall -I./include

TARGET=main

_OBJ = clist.o position.o $(TARGET).o 
OBJ = $(patsubst %,bin/%,$(_OBJ))

_DEPS = clist.h position.h
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
