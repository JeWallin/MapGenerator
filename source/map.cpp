#include "../header/map.h"
#include "stdlib.h"
#include <iostream>
#include <time.h>

int const MaxRooms = 7;
int const MinRooms = 4;

Map::Map(int w, int h)
{
    this->width = w;
    this->height = h;

    for( int i = 0; i < this->width; ++i)
    {
        this->mapElements.push_back(std::vector<MapElement>());
        for( int j = 0; j < this->height; ++j)
        {
            this->mapElements.back().push_back(MapElement::Wall);
        }
    }
    
}



void Map::GenerateRooms()
{
    srand (time(NULL));
    int numberOfRooms = rand() % (MaxRooms-MinRooms) + MinRooms;

    for ( int i = 0; i < numberOfRooms; i++)
    {
        int width = rand() % 6 + 6;
        int height = rand() % 6 + 6;
        int x = 1 + rand() %(this->width - width -1);
        int y = 1 + rand() %(this->height - height -1);

        this->roomCenters.push_back(coord(x+(width/2),y+(height/2)));

        for ( int i = 0; i < width; ++i)
        {
            for ( int j = 0; j < height; ++j)
            {
                int mX = x + i;
                int mY = y + j;
                int free = 0;

                this->mapElements[mX][mY] = MapElement::Walkable;
            }
        }
    }
    for ( int i = 1; i < this->roomCenters.size(); ++i)
    {
        coord Moving = this->roomCenters[i-1];
        coord To = this->roomCenters[i];
        std::cout << To.x << " " << To.y << std::endl;
        while (!(Moving.x == To.x && Moving.y == To.y))
        {
            if ( Moving.x < To.x)
            {
                Moving.x += 1;
            }
            else if(Moving.x > To.x)
            {
                Moving.x -= 1;
            }
            else if ( Moving.x == To.x )
            {
                if ( Moving.y < To.y)
                {
                    Moving.y += 1;
                }
                else if(Moving.y > To.y)
                {
                    Moving.y -= 1;
                }
            }
            std::cout << Moving.x << " " << Moving.y << std::endl;
            this->mapElements[Moving.x][Moving.y] = MapElement::Walkable;
        }
        
    }
    
}

void Map::PrintMap()
{
    for(int i = 0; i < this->mapElements.size(); ++i)
    {
        for( int j = 0; j < this->mapElements[i].size(); ++j)
        {
            if ( this->mapElements[j][i] == Walkable)
            {
                std::cout << ".";
            }
            else
            {
                std::cout << "X";
            }
        }
        std::cout << std::endl;
    }
}
