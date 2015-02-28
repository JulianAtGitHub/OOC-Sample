
cc=clang
binary=sample1
objects=Set.o main.o

$(binary): $(objects)
	cc -o $(binary) $(objects)
Set.o: Set.c
main.o: main.c

clean:
	rm $(binary) $(objects)
