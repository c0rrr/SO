read: main.o read.o
	gcc -o read main.o read.o
main.o: main.c read.h
	gcc -c main.c
read.o: read.c read.h
	gcc -c read.c
clean:
	rm -f *.o read
