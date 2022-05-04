OBJ = main.o
all: pthreads
pthreads: $(OBJ)
	gcc -O3 $(OBJ) -pthread -o pthreads
.PHONY: clean
clean:
	rm -f *.o pthreads
