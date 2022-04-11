OBJ = main.o copy.o
all: projekt
projekt: $(OBJ)
	gcc $(OBJ) -o projekt
$(OBJ):copy.h
.PHONY: clean
clean:
	rm -f *.o projekt
