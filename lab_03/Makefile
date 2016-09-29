pose_db: bin bin/clist.o bin/main.o
	gcc bin/clist.o bin/main.o -o pose_db
bin:
	mkdir -p bin
bin/clist.o: src/clist.c include/clist.h    
	gcc -c -I./include src/clist.c -o bin/clist.o 
bin/main.o: src/main.c include/clist.h  
	gcc -c -I./include src/main.c -o bin/main.o 
clean:
	rm -rf bin
	rm -rf pose_db