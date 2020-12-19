all: main.o functions.o parse.o
	gcc -o program main.o functions.o parse.o

main.o: main.c functions.h parse.h
	gcc -c main.c 

functions.o: functions.c functions.h
	gcc -c functions.c 

parse.o: parse.c parse.h
	gcc -c parse.c
clean: 
	rm *.o
  
run:
	./program
