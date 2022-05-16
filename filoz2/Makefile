OBJ = main.o
all: filoz
filoz: $(OBJ)
	gcc -O3 $(OBJ) -pthread -o filoz

.PHONY: clean
clean:
	rm -f *.o filoz
