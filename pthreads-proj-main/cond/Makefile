OBJ = main.o ../functions.o

all: cond

cond: $(OBJ)
	gcc $(OBJ) -o cond -pthread

$(OBJ): ../functions.h

.PHONY: clean
clean:
	rm -f *.o
