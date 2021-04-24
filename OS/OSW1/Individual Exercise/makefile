main: main.o sum.o sub.o
	gcc -o main main.o sum.o sub.o
main.o: main.c sum.h  
	gcc -c main.c  
sum.o: sum.c sum.h  
	gcc -c sum.c  
sub.o: sub.c sub.h
	gcc -c sub.c
clean:
	rm -f *.o
