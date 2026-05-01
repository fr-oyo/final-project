#include "room.h"

Room::Room(){
    type = DEFAULT;
    id = -1;
    x = 0;
    y = 0;
    visited = false;

    up = false;
    down = false;
    left = false;
    right = false;
}

Room::Room(RoomType type, int id, int x, int y){
    this->type = type;
    this->id = id;
    this->x = x;
    this->y = y;
    visited = false;

    up = false;
    down = false;
    left = false;
    right = false;
}

Room::~Room(){
    //empty...
}

RoomType Room::getType() const{
    return type;
}

int Room::getId() const{
    return id;
}

int Room::getX() const{
    return x;
}
int Room::getY() const{
    return y;
}

bool Room::isVisited() const{
    return visited;
}

bool Room::hasUp() const{
    return up;
}
bool Room::hasDown() const{
    return down;
}
bool Room::hasLeft() const{
    return left;
}
bool Room::hasRight() const{
    return right;
}

string Room::getTypeName() const{
    switch (type){
        case START:
            return "Start";
        case DEFAULT:
            return "Enemies";
        case TREASURE:
            return "Treasure";
        case BOSS:
            return "Boss";
        case REST:
            return "Rest";
        default:
            return "Unknown";
    }
}

char Room::getSymbol() const{
    switch (type){
        case START:
            return '.';
        case DEFAULT:
            return '.';
        case TREASURE:
            return '.';
        case BOSS:
            return '!';
        case REST:
            return '+';
        default:
            return '?';
    }
}

void Room::setType(RoomType type){
    this->type = type;
}
void Room::setVisited(bool visited){
    this->visited = visited;
}

void Room::setUp(bool x){
    up = x;
}
void Room::setDown(bool x){
    down = x;
}
void Room::setLeft(bool x){
    left = x;
}
void Room::setRight(bool x){
    right = x;
}