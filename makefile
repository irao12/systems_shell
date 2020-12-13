all: main.o functions.o cd.o
	gcc -o program main.o functions.o cd.o 

main.o: main.c functions.h cd.h
	gcc -c main.c 

functions.o: functions.c functions.h
	gcc -c functions.c 

cd.o: cd.c cd.h
	gcc -c cd.c

clean: 
	rm *.o
  
run:
	./program
