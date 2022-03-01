OBJ = main.o function.o
all: hello
hello: $(OBJ)
	gcc $(OBJ) -o hello
$(OBJ): function.h
.PHONY: clean
clean:
	rm -f *.o hello
