
CC = gcc
binary = sample1
objects = new.o String.o main.o

# generate debug symbol with option -g
CFLAGS = -g

$(binary): $(objects)
	CC -o $(binary) $(objects)
new.o: new.c
String.o: String.c
main.o: main.c

clean:
	rm $(binary) $(objects)

cleanMinGW:
	rm $(binary).exe $(objects)
