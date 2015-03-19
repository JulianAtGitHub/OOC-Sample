
CC = gcc
binary = sample1
objects = new.o point.o circle.o main.o

# generate debug symbol with option -g
CFLAGS = -g

$(binary): $(objects)
	CC -o $(binary) $(objects)
new.o: new.c
point.o: point.c
circle.o: circle.c
main.o: main.c

clean:
	rm $(binary) $(objects)

cleanMinGW:
	rm $(binary).exe $(objects)