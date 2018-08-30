#include "../header/MapGenerator.h"
#include <iostream>
#include <algorithm> 

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

void MapGenerator::CreatePaths()
{
    for ( int i = 1; i < Rooms.size(); ++i)
    {
        Coordinate start = Rooms[i-1].GetCenter();
        Coordinate goal = Rooms[i].GetCenter();
        
        start.x = std::min(start.x, MapSize.x-1);
        start.y = std::min(start.y, MapSize.y-1);
        goal.x = std::min(goal.x, MapSize.x-1);
        goal.y = std::min(goal.y, MapSize.y-1);

        while(!(start.x == goal.x && start.y == goal.y))
        {
            if ( start.x != goal.x )
            {
                int dif = goal.x - start.x;
                dif /= abs(dif);
                
                start.x += dif;
            }
            else
            {
                int dif = goal.y - start.y;
                dif /= abs(dif);

                start.y += dif;
            }
            
            Map[start.x][start.y] = MapEntety::WALKABLE;
        }
    }
}

void MapGenerator::GenerateRooms()
{
    int roomVari = NumberOfRooms.max - NumberOfRooms.min + 1;
    int numberOfRooms = rand()%roomVari + NumberOfRooms.min;
    if ( RoomType == RoomShape::BOXES )
    {
        GenerateBoxRooms(numberOfRooms);
    }  
}

void MapGenerator::RemoveDummyWalls()
{
    std::vector< Coordinate > ToRemove;
    for ( int x = 0; x < Map.size(); ++x)
    {
        for ( int y = 0; y < Map[x].size(); ++y)
        {
            int counter = 0;
            if ( Map[x][y] == MapEntety::WALL )
            {
                Coordinate left(std::max(0, x-1),y);
                Coordinate up(x, std::max(0, y-1));
                Coordinate right( std::min(MapSize.x-1, x+1), y);
                Coordinate down(x, std::min(MapSize.y-1, y+1));

                counter += Map[left.x][left.y] == MapEntety::WALKABLE ? 1 : 0;
                counter += Map[right.x][right.y] == MapEntety::WALKABLE ? 1 : 0;
                counter += Map[up.x][up.y] == MapEntety::WALKABLE ? 1 : 0;
                counter += Map[down.x][down.y] == MapEntety::WALKABLE ? 1 : 0;


                if ( counter == 0)
                {
                    ToRemove.push_back(Coordinate(x,y));
                }
            }

            
        }
    }

    for ( int i = 0; i < ToRemove.size(); ++i)
    {
        Coordinate c = ToRemove[i];
        Map[c.x][c.y] = MapEntety::NONE; 
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
    // Create Paths
    CreatePaths();
    // Clear dummy Walls
    RemoveDummyWalls();
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

                case MapEntety::NONE:
                    std::cout << " ";
                    break;

                default:
                    std::cout << "-";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

MapGenerator::~MapGenerator()
{

}