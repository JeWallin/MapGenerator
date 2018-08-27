#ifndef ROOM_H
#define ROOM_H
class Room 
{
public:
    Room();
    Room(int, int);
    int GetSize() const;

    int GetWidth() const;
    int GetHeight() const;
    int GetX() const;
    int GetY() const;

    void SetWorldPosition(int, int);
private:
    int width;
    int height;

    int x;
    int y;
};
#endif