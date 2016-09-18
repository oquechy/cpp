lab2: bin bin/str.o bin/test_str.o bin/test.o
	g++ bin/test.o bin/test_str.o bin/str.o -o lab2
bin:
	mkdir -p bin
bin/str.o: src/str.cpp include/str.h    
	g++ -c -I./include src/str.cpp -o bin/str.o 
bin/test_str.o: src/test_str.cpp include/test_str.h include/str.h  
	g++ -c -I./include src/test_str.cpp -o bin/test_str.o 
bin/test.o: src/test.cpp include/test_str.h include/str.h 
	g++ -c -I./include src/test.cpp -o bin/test.o 
clean:
	rm -rf bin
	rm -rf lab2