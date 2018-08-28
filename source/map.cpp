#include "../header/map.h"
#include "stdlib.h"
#include <iostream>
#include <time.h>

int const MaxRooms = 7;
int const MinRooms = 4;

Map::Map(int w, int h)
{
    srand (time(NULL));
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

void Map::GenerateRooms(bool overlapping, bool boxRoom, coord rooms, coord roomSize)
{
    int numberOfRooms = rand() % (rooms.y-rooms.x) + rooms.x;

    std::vector<room> currentRooms;
    int tries = 10;
    // create rooms
    for ( int i = 0; i < numberOfRooms; i++)
    {
        int width = 1 + (rand() % roomSize.x) + roomSize.y;
        int height = 1 + (rand() % roomSize.x) + roomSize.y;
        int x = 1 + rand() %(this->width - width);
        int y = 1 + rand() %(this->height - height);

        room newRoom(x, y, width, height);

        bool createRoom = true;
        if(!overlapping)
        {
            for ( int i = 0; i < currentRooms.size(); ++i)
            {
                if( boxRoom )
                {
                    if ( newRoom.BoxCollide(currentRooms[i]))
                    {
                        createRoom = false;
                        if ( --tries != 0)
                        {
                            --i;
                        }
                        break;
                    }
                }
                else
                {
                    if ( newRoom.SphereCollide(currentRooms[i]))
                    {
                        createRoom = false;
                        if ( --tries != 0)
                        {
                            --i;
                        }
                        break;
                    }
                }
            }
        }  
        

        if ( createRoom )
        {
            std::cout << newRoom.height << " " << newRoom.width << std::endl;
            currentRooms.push_back(newRoom);
        } 
    }
    // update mape
    for ( int i = 0; i < this->mapElements.size(); ++i)
    {
        for ( int j = 0; j < this->mapElements[i].size(); ++j)
        {
            bool Walkable = false;
            for ( int roomNr = 0; roomNr < currentRooms.size(); ++roomNr)
            {
                room swagDot(i, j, 0, 0);
                if( boxRoom )
                {
                    if ( swagDot.BoxCollide(currentRooms[roomNr]) )
                    {
                        Walkable = true;
                        break;
                    }
                }
                else
                {
                    if ( swagDot.SphereCollide(currentRooms[roomNr]) )
                    {
                        Walkable = true;
                        break;
                    }
                }
            }
            if (Walkable)
            {
                this->mapElements[i][j] = MapElement::Walkable;
            }
        }
    }

    for ( int i = 1; i < currentRooms.size(); ++i)
    {
        coord Moving = currentRooms[i-1].GetCenter();
        coord To = currentRooms[i].GetCenter();
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
