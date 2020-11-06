render: main.o light.h sphere.o geometry.o
	g++ geometry.o sphere.o light.h main.o -o main

main.o: main.cpp
	g++ -c main.cpp

sphere.o: sphere.cpp
	g++ -c sphere.cpp

geometry.o: geometry.cpp
	g++ -c geometry.cpp

clean:
	rm -rf *.o