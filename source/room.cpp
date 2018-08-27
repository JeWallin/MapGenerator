#include "../header/room.h"

Room::Room()
{
    this->width = 10;
    this->height = 10;
    this->SetWorldPosition(0,0);
}

Room::Room(int w, int h)
{
    this->width = w;
    this->height = h;
    this->SetWorldPosition(0,0);
}

int Room::GetSize() const
{
    return this->width*this->height;
}

int Room::GetHeight() const
{
    return this->height;
}

int Room::GetWidth() const
{
    return this->width;
}

int Room::GetX() const
{
    return this->x;
}

int Room::GetY() const
{
    return this->y;
}
void Room::SetWorldPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}