
cc=clang
binary=sample2
objects=Set.o main.o

$(binary): $(objects)
	cc -o $(binary) $(objects)
Set.o: Set.c
main.o: main.c

clean:
	rm $(binary) $(objects)
