#ifndef MAP_H
#define MAP_H
#include <vector>
#include "room.h"


enum MapElement
{
    Wall,
    Walkable
};

struct coord
{
    int x;
    int y;

    coord(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};

class Map
{
public:
    Map(int, int);
    void GenerateRooms();
    void PrintMap();

private:
    int width;
    int height;
    std::vector<coord> roomCenters;
    std::vector< std::vector<MapElement> > mapElements;
};
#endif