lab1: bin/main.o bin/algorithm.o bin/util.o bin/io.o
	mkdir -p bin
	gcc bin/main.o bin/algorithm.o bin/util.o bin/io.o -o lab1
bin/main.o: src/main.c
	gcc -c -I./include src/main.c -o bin/main.o
bin/algorithm.o: src/algorithm.c
	gcc -c -I./include src/algorithm.c -o bin/algorithm.o
bin/util.o: src/util.c
	gcc -c -I./include src/util.c -o bin/util.o
bin/io.o: src/io.c
	gcc -c -I./include src/io.c -o bin/io.o
clean:
	rm -rf bin
