OBJ = main.o serialize.o
all: serialize
serialize: $(OBJ)
	gcc $(OBJ) -o serialize
$(OBJ):serialize.h
.PHONY: clean
clean:
	rm -f *.o serialize
