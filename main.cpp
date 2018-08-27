#include <iostream>
#include <vector>

#include "header/map.h"

int main()
{
    
    Map map(40, 40);
    
    map.GenerateRooms();
    
    map.PrintMap();

    return 0;
}