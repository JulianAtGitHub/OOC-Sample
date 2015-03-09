
CC = gcc
binary = sample1
objects = value.o parse.o main.o

# generate debug symbol with option -g
CFLAGS = -g

$(binary): $(objects)
	CC -o $(binary) $(objects)
value.o: value.c
parse.o: parse.c
main.o: main.c

clean:
	rm $(binary) $(objects)

cleanMinGW:
	rm $(binary).exe $(objects)
