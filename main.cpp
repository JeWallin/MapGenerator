#include <iostream>
#include <vector>

#include "header/map.h"
#include "header/MapGenerator.h"
int main()
{
    
    MapGenerator mg;

    mg.SetRoomSize(Span(7, 12));
    mg.SetNumberOfRooms(Span(2, 5));
    mg.SetAllowedIntersection(true);
    mg.GenerateMap();

    mg.PrintMap();

    return 0;
}