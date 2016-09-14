lab1: clean bin bin/main.o bin/algorithm.o bin/util.o bin/io.o
	gcc bin/main.o bin/algorithm.o bin/util.o bin/io.o -o lab1
bin:
	mkdir -p bin
bin/main.o: src/main.c include/algorithm.h include/io.h    
	gcc -c -I./include src/main.c -o bin/main.o
bin/algorithm.o: src/algorithm.c include/algorithm.h include/util.h include/io.h  
	gcc -c -I./include src/algorithm.c -o bin/algorithm.o
bin/util.o: src/util.c include/util.h include/io.h 
	gcc -c -I./include src/util.c -o bin/util.o
bin/io.o: src/io.c include/io.h 
	gcc -c -I./include src/io.c -o bin/io.o
clean:
	rm -rf bin
	rm -rf lab1