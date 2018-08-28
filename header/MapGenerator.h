#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H

#include "helper.h"
#include <vector>

class MapGenerator
{
private:
    // How big is the map
    Coordinate MapSize;
    // Can room intersect
    bool AllowIntersection;
    // Are the rooms boxes
    RoomShape RoomType;
    // Describes the number of rooms to be generated. (try to)
    Span NumberOfRooms;
    // Describes the whished size of rooms.
    Span RoomSize;


    //The world map
    std::vector< std::vector<MapEntety> > Map;
    std::vector<Room> Rooms;

    void CreateWorldOfWalls();
    void GenerateBoxRooms(int);
    void PlaceRoomsInWorld();
    void CreatePaths();
    void GenerateRooms();
    void RemoveDummyWalls();
public:
    MapGenerator();

    void SetAllowedIntersection(bool);
    void SetRoomShape(RoomShape);
    void SetNumberOfRooms(Span);
    void SetRoomSize(Span);

    void GenerateMap();
    void PrintMap();

    ~MapGenerator();
};



#endif //MAP_GENERATOR_H