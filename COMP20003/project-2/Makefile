all: map1 map2

map1: map1.o read.o kdtree.o dict.o utils.o data.o
	gcc -Wall -o map1 map1.o read.o kdtree.o dict.o utils.o data.o -lm -g

map2: map2.o read.o kdtree.o dict.o utils.o data.o
	gcc -Wall -o map2 map2.o read.o kdtree.o dict.o utils.o data.o -lm -g

map2.o: map2.c read.h
	gcc -Wall -c -o map2.o map2.c -g

map1.o: map1.c read.h
	gcc -Wall -c -o map1.o map1.c -g

read.o: read.c read.h
	gcc -Wall -c -o read.o read.c -g
    
kdtree.o: kdtree.c kdtree.h
	gcc -Wall -c -o kdtree.o kdtree.c -g

dict.o: dict.c dict.h
	gcc -Wall -c -o dict.o dict.c -g

utils.o: utils.c utils.h
	gcc -Wall -c -o utils.o utils.c -g

data.o: data.c data.h
	gcc -Wall -c -o data.o data.c -g
