OBJ = main.o
all: mutex
mutex: $(OBJ)
	gcc $(OBJ) -pthread -o mutex
.PHONY: clean
clean:
	rm -f *.o mutex
