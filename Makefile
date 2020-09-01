all: memgrind.c mymalloc.o
	gcc -g memgrind.c mymalloc.o -o memgrind

mymalloc.o: mymalloc.c
	gcc -g -c mymalloc.c

clean:
	rm -rf memgrind; rm -rf mymalloc.o
