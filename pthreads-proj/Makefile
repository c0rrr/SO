fryzjer: main.o fmutex.o fvaria.o utils.o
	gcc -o fryzjer -O3 -pthread main.o fmutex.o fvaria.o utils.o
main.o: main.c fmutex.h fvaria.h utils.h
	gcc -c main.c
fmutex.o: fmutex.c fmutex.h
	gcc -c fmutex.c
fvaria.o: fvaria.c fvaria.h
	gcc -c fvaria.c
utils.o: utils.c utils.h
	gcc -c utils.c
clean:
	rm -f *.o fryzjer
