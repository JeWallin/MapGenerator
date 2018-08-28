#include "../header/MapGenerator.h"
#include <iostream>

MapGenerator::MapGenerator()
{
    srand(time(NULL));
    MapSize = Coordinate(42, 42);
    AllowIntersection = true;
    RoomType = RoomShape::BOXES;
    NumberOfRooms = Span(3, 7);
    RoomSize = Span(4, 10);
}

void MapGenerator::CreateWorldOfWalls()
{
    for ( int x = 0; x < MapSize.x; ++x)
    {
        Map.push_back(std::vector<MapEntety>());
        for ( int y = 0; y < MapSize.y; ++y)
        {
            Map.back().push_back(MapEntety::WALL);
        }
    }
}

void MapGenerator::GenerateBoxRooms( int numberOfRoons )
{
    // +1 because % will give us a random value from 0 to (roomVari-1);
    int roomVari = RoomSize.max - RoomSize.min + 1;
    for( int i = 0; i < numberOfRoons; ++i)
    {
        Coordinate c(
            rand()%MapSize.x, 
            rand()%MapSize.y
            );

        SizeStruct s(
            rand()%roomVari + RoomSize.min, 
            rand()%roomVari + RoomSize.min
            );
        Room r;

        r.coordinate = c;
        r.size = s;

        if ( AllowIntersection )
        {
            Rooms.push_back(r);
        }
        else
        {
            bool add = true;
            for ( int i = 0; i < Rooms.size(); ++i)
            {
                if (r.Colliding(Rooms[i]))
                {
                    add = false;
                    break;
                }
            }

            if( add )
            {
                Rooms.push_back(r);
            }
        }
    }
}

void MapGenerator::PlaceRoomsInWorld()
{
    for ( int x = 0; x < Map.size(); ++x)
    {
        for ( int y = 0; y < Map[x].size(); ++y)
        {
            Coordinate c(x,y);
            SizeStruct s(0,0);

            Room r;
            r.coordinate = c;
            r.size = s;

            for ( int roomIndex = 0; roomIndex < Rooms.size(); ++roomIndex )
            {
                if ( r.Colliding(Rooms[roomIndex]) )
                {
                    Map[c.x][c.y] = MapEntety::WALKABLE;
                    break;
                }
            }
        }
    }
}

void MapGenerator::GenerateRooms()
{
    int numberOfRooms = 10;
    if ( RoomType == RoomShape::BOXES )
    {
        GenerateBoxRooms(numberOfRooms);
    }  
}


void MapGenerator::SetAllowedIntersection( bool intersection )
{
    AllowIntersection = intersection;
}

void MapGenerator::SetRoomShape( RoomShape shape )
{
    RoomType = shape;
}

void MapGenerator::SetNumberOfRooms( Span rooms )
{
    NumberOfRooms = rooms;
}

void MapGenerator::SetRoomSize( Span size )
{
    RoomSize = size;
}

void MapGenerator::GenerateMap()
{
    // Fill the world with walls.
    CreateWorldOfWalls();
    // place rooms
    GenerateRooms();
    // Remove walls Where rooms are
    PlaceRoomsInWorld();
}

void MapGenerator::PrintMap()
{
    for ( int x = 0; x < MapSize.x; ++x)
    {
        for ( int y = 0; y < MapSize.y; ++y)
        {
            
            switch (Map[x][y])
            {
                case MapEntety::WALL:
                    std::cout << "x";
                    break;
            
                case MapEntety::WALKABLE:
                    std::cout << ".";
                    break;

                default:
                    std::cout << " ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

MapGenerator::~MapGenerator()
{

}