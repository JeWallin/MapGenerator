#include <iostream>
#include <vector>

#include "header/map.h"
#include "header/MapGenerator.h"
int main()
{
    
    MapGenerator mg;

    mg.SetRoomSize(Span(3, 7));

    mg.GenerateMap();

    mg.PrintMap();

    return 0;
}