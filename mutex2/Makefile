OBJ = main.o
all: mutex
mutex: $(OBJ)
	gcc -O3 $(OBJ) -pthread -o mutex
.PHONY: clean
clean:
	rm -f *.o mutex
