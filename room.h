#ifndef ROOM_H
#define ROOM_H

#include <string>
using namespace std;

enum RoomType{
    START,
    DEFAULT,
    BOSS,
    TREASURE,
    REST
};

class Room {
    private:
        RoomType type;
        int id;
        int x;
        int y;
        bool visited;

        bool up;
        bool down;
        bool left;
        bool right;

    public:
        Room();
        Room(RoomType type, int id, int x, int y);
        ~Room();

        RoomType getType() const;
        int getId() const;
        int getX() const;
        int getY() const;
        bool isVisited() const;

        bool hasUp() const;
        bool hasDown() const;
        bool hasLeft() const;
        bool hasRight() const;

        void setType(RoomType type);
        void setVisited(bool visited);

        void setUp(bool x);
        void setDown(bool x);
        void setLeft(bool x);
        void setRight(bool x);

        string getTypeName() const;
        char getSymbol() const;

    };

#endif