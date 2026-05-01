#include "dungeon.h"

#include <iostream>
#include <cstdlib>
using namespace std;

Dungeon::Dungeon(int c_view){
    this->c_view = c_view;
    currentDepth = 0;
    boss_check = false;
    currentRoom = Room(START, 0);
}

Dungeon::~Dungeon(){
    //empty...
}

Room Dungeon::getCurrentRoom() const{
    return currentRoom;
}

int Dungeon::getCurrentDepth() const{
    return currentDepth;
}

vector<Room> Dungeon::getPreviousRooms() const{
    return previousRooms;
}

vector<Room> Dungeon::generateNextRooms(int depth){
    vector<Room> rooms;
}