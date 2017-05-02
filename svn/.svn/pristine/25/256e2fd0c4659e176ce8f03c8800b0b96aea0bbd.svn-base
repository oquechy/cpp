CC=g++
CFLAGS=-c -I./include -std=c++11 -pedantic -Wall -Wextra -Werror

TARGET=main

_OBJ = $(TARGET).o matrix.o
OBJ = $(patsubst %,bin/%,$(_OBJ))

_DEPS = matrix.h
DEPS = $(patsubst %,include/%,$(_DEPS))

#_TOBJ =
#TOBJ = $(patsubst %,bin/%,$(_TOBJ))

#_TDEPS =
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
