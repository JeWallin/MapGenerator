output: main.o MapGenerator.o
	g++ main.o MapGenerator.o -o output

main.o: main.cpp
	g++ -c main.cpp

MapGenerator.o: source/MapGenerator.cpp header/MapGenerator.h header/helper.h
	g++ -c source/MapGenerator.cpp

clean: 
	rm *.o output 