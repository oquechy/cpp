lab2: bin bin/str.o bin/test_str.o bin/test.o
	gcc bin/test.o bin/str.o bin/test_str.o -o lab2 -std=c11
bin:
	mkdir -p bin
bin/str.o: src/str.c include/str.h    
	gcc -c -I./include src/str.c -o bin/str.o -std=c11
bin/test_str.o: src/test_str.c include/test_str.h include/str.h  
	gcc -c -I./include src/test_str.c -o bin/test_str.o -std=c11
bin/test.o: src/test.c include/test_str.h include/str.h 
	gcc -c -I./include src/test.c -o bin/test.o -std=c11
clean:
	rm -rf bin
	rm -rf lab2