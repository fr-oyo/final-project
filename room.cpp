#include "room.h"

Room::Room(){
    type = START;
    depth = 0;
}

Room::Room(RoomType type, int depth){
    this->type = type;
    this->depth = depth;
}

Room::~Room(){
    //empty...
}

RoomType Room::getType() const{
    return type;
}

int Room::getDepth() const{
    return depth;
}

void Room::setType(RoomType type){
    this->type = type;
}

void Room::setDepth(int depth){
    this->depth = depth;
}

string Room::getTypeName() const{
    switch (type){
        case START:
            return "Start Room";
        case DEFAULT:
            return "Enemies";
        case TREASURE:
            return "Treasure Room";
        case BOSS:
            return "Boss Room";
        case REST:
            return "Campfire";
        default:
            return "Unknown";
    }
}