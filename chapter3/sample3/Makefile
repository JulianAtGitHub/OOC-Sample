
CC = gcc
binary = sample3
objects = infix.o parse.o main.o

# generate debug symbol with option -g
CFLAGS = -g

$(binary): $(objects)
	CC -o $(binary) $(objects)
infix.o: infix.c
parse.o: parse.c
main.o: main.c

clean:
	rm $(binary) $(objects)

cleanMinGW:
	rm $(binary).exe $(objects)
