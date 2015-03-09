
CC = gcc
binary = sample2
objects = postfix.o parse.o main.o

# generate debug symbol with option -g
CFLAGS = -g

$(binary): $(objects)
	CC -o $(binary) $(objects)
postfix.o: postfix.c
parse.o: parse.c
main.o: main.c

clean:
	rm $(binary) $(objects)

cleanMinGW:
	rm $(binary).exe $(objects)
