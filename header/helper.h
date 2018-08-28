#ifndef HELPER_H
#define HELPER_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum MapEntety
{
    WALL = 0,
    WALKABLE = 1,
    NONE = 2
};

enum RoomShape
{
    BOXES,
    SPHERES
};

struct Span
{
    int min;
    int max;

    Span()
    {
        min = 1;
        max = 10;
    }

    Span(int _min, int _max)
    {
        min = _min;
        max = _max;
    }
};

struct Coordinate
{
    int x;
    int y;

    Coordinate()
    {
        x = 0;
        y = 0;
    }

    Coordinate( int _x, int _y )
    {
        x = _x;
        y = _y;
    }

    float distanceTo( Coordinate coord )
    {
        int a = x - coord.x;
        int b = y - coord.y;

        float c = a*a + b*b;

        return sqrt(c);
    }
};

struct SizeStruct
{
    int width;
    int height;

    SizeStruct()
    {
        width = 0;
        height = 0;
    }
    SizeStruct(int w, int h)
    {
        width = w;
        height = h;
    }
};

struct Room
{
    Coordinate coordinate;
    SizeStruct size;

    Room(){
        coordinate = Coordinate(0,0);
        size = SizeStruct(0,0);
    }

    bool Colliding( const Room& r ) const
    {
        return (abs(coordinate.x - r.coordinate.x) * 2 < (size.width + r.size.width)) &&
            (abs(coordinate.y - r.coordinate.y) * 2 < (size.height + r.size.height));
    }

    Coordinate GetCenter() const
    {
        Coordinate c( coordinate.x, coordinate.y );

        //c.x += size.width/4;
        //c.y += size.height/4;

        return c;
    }

};

#endif //HELPER_H