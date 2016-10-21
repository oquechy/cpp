CC=gcc
CFLAGS=-c -Wall -I./include

TARGET=main

_OBJ = phonebook.o $(TARGET).o 
OBJ = $(patsubst %,bin/%,$(_OBJ))

_DEPS = names.h phonebook.h
DEPS = $(patsubst %,include/%,$(_DEPS))

$(TARGET): bin $(OBJ) 
	$(CC) $(OBJ) -lexpat -o $@

bin:
	mkdir -p $@

bin/%.o: src/%.c $(DEPS)    
	$(CC) $(CFLAGS) $< -o $@ 
                                        
.PHONY : clean

clean:
	rm -rf bin $(TARGET)
