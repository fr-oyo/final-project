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
        int depth;

    public:
        Room();
        Room(RoomType type, int depth);
        ~Room();

        RoomType getType() const;
        int getDepth() const;

        void setType(RoomType type);
        void setDepth(int depth);

        string getTypeName() const;

    };

#endif