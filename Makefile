CC=g++

all: render

render: main.o light.h sphere.o geometry.o
	$(CC) geometry.o sphere.o light.h main.o -o main

main.o: main.cpp
	$(CC) -c main.cpp

sphere.o: sphere.cpp
	$(CC) -c sphere.cpp

geometry.o: geometry.cpp
	$(CC) -c geometry.cpp

clean:
	rm -rf *.o