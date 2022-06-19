fryzjer: main.o mutex.o varia.o 
	gcc -o fryzjer -O3 -pthread main.o mutex.o varia.o 
main.o: main.c mutex.h varia.h 
	gcc -c main.c
mutex.o: mutex.c mutex.h
	gcc -c mutex.c
varia.o: varia.c varia.h
	gcc -c varia.c
clean:
	rm -f *.o fryzjer
