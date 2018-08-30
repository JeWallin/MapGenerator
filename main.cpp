#include <iostream>
#include <vector>

#include "header/MapGenerator.h"
int main()
{
    
    MapGenerator mg;

    mg.SetRoomSize(Span(9, 12));
    mg.SetNumberOfRooms(Span(6, 12));
    mg.SetAllowedIntersection(false);
    mg.GenerateMap();

    mg.PrintMap();

    return 0;
}