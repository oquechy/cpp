lab1:
	mkdir -p bin
	gcc bin/main.o bin/algorithm.o bin/utils.o bin/io.o -o lab1
bin/main.o:
	gcc -c -I./include src/main.c -o bin/main.o
bin/algorithm.o:
	gcc -c -I./include src/algorithm.c -o bin/algorithm.o
bin/utils.o:
	gcc -c -I./include src/utilc.c -o bin/utils.o
clean:
	rm -rf bin