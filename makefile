output: map.o main.o
	g++ main.o map.o -o output

main.o: main.cpp
	g++ -c main.cpp


map.o: source/map.cpp header/map.h
	g++ -c source/map.cpp

clean: 
	rm *.o output