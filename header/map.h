#ifndef MAP_H
#define MAP_H

#include <vector>
#include <math.h>

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

struct room 
{
    int x;
    int y;
    int width;
    int height;

    room()
    {
        x = y = 0;
        width = height = 1;
    }

    room(int _x, int _y, int _w, int _h) : x(_x), y(_y), width(_w), height(_h)
    {

    }

    bool BoxCollide( const room& box ) const
    {
        return (abs(x - box.x) * 2 < (width + box.width)) &&
            (abs(y - box.y) * 2 < (height + box.height));
    }

    bool SphereCollide( const room& sphere) const
    {  
        int myRadius = (width + height)/2;
        int otherRadius = ( sphere.width + sphere.height)/2;

        int distanceX = abs( x - sphere.x);
        int distanceY = abs( y - sphere.y);

        float distance = sqrt(distanceX*distanceX + distanceY*distanceY);

        return distance < (myRadius + otherRadius);
    }

    coord GetCenter()
    {
        return coord( x , y);
    }
};

class Map
{
public:
    Map(int, int);
    void GenerateRooms();
    void GenerateRooms(bool overlapping, bool boxRoom, coord rooms, coord roomSize);
    void PrintMap();

private:
    int width;
    int height;
    std::vector<coord> roomCenters;
    std::vector< std::vector<MapElement> > mapElements;
};
#endif