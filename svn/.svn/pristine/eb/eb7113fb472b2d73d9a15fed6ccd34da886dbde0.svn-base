CC=g++
CFLAGS=-c -I./include -std=c++11 -pedantic -Wall -Wextra -Werror

TARGET=main

_OBJ = $(TARGET).o
OBJ = $(patsubst %,bin/%,$(_OBJ))

_DEPS = my_array.h
DEPS = $(patsubst %,include/%,$(_DEPS))

#_TOBJ = BoardTest.o Test.o test.o Board.o BoardView.o
#TOBJ = $(patsubst %,bin/%,$(_TOBJ))

#_TDEPS = BoardTest.h Test.h
#TDEPS = $(patsubst %,test/%,$(_TDEPS))

all: $(TARGET)

#test: $(TOBJ)
#	$(CC) $(TOBJ) -o $@.exe

$(TARGET): bin $(OBJ)
	$(CC) $(OBJ) -o $@

bin:
	mkdir -p $@

bin/%.o: src/%.cpp $(DEPS)
	$(CC) $(CFLAGS) $< -o $@

#bin/%.o: test/%.cpp $(TDEPS)
#	$(CC) $(CFLAGS) $< -o $@

.PHONY : clean

clean:
	rm -rf bin $(TARGET)
