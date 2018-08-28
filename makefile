output: map.o main.o MapGenerator.o
	g++ main.o map.o MapGenerator.o -o output

main.o: main.cpp
	g++ -c main.cpp

MapGenerator.o: source/MapGenerator.cpp header/MapGenerator.h header/helper.h
	g++ -c source/MapGenerator.cpp

map.o: source/map.cpp header/map.h
	g++ -c source/map.cpp

clean: 
	rm *.o output