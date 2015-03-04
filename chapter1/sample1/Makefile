
CC = gcc
binary = sample1
objects = Set.o main.o

# generate debug symbol with option -g
CFLAGS = -g

$(binary): $(objects)
	CC -o $(binary) $(objects)
Set.o: Set.c
main.o: main.c

clean:
	rm $(binary) $(objects)

cleanMinGW:
	rm $(binary).exe $(objects)