CC=g++
CFLAGS=-c -g -I./src -I./test -Wall -Werror -std=c++11

TARGET=main

_OBJ = huffman.o bitstream.o $(TARGET).o
OBJ = $(patsubst %,bin/%,$(_OBJ))

_DEPS = huffman.h bitstream.h
DEPS = $(patsubst %,src/%,$(_DEPS))

_TOBJ = huffman.o bitstream.o huffman_test.o autotest.o test.o
TOBJ = $(patsubst %,bin/%,$(_TOBJ))

_TDEPS = autotest.h bitstream.h huffman_test.h huffman.h
TDEPS = $(patsubst %,test/%,$(_TDEPS))

all: $(TARGET)

test: $(TOBJ)
	$(CC) $(TOBJ) -o bin/$@

$(TARGET): bin $(OBJ)
	$(CC) $(OBJ) -o $@

bin:
	mkdir -p $@

bin/%.o: src/%.cpp $(DEPS)
	$(CC) $(CFLAGS) $< -o $@

bin/%.o: test/%.cpp $(TDEPS)
	$(CC) $(CFLAGS) $< -o $@

.PHONY : clean

clean:
	rm -rf bin $(TARGET) bin/test