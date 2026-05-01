#ifndef DUNGEON_H
#define DUNGEON_H

#include "Room.h"
#include <vector>
using namespace std;

class Dungeon{
    private:
        Room currentRoom;
        int currentDepth;
        int c_view;
        bool boss_check;

        vector<Room> previousRooms;

    public:
        Dungeon(int c_view);
        ~Dungeon();

        Room getCurrentRoom() const;
        int getCurrentDepth() const;
        bool getBossCheck() const;
        vector<Room> getPreviousRooms() const;

        vector<Room> generateNextRooms(int depth);
        vector<vector<Room>> lookAhead();

        void moveToRoom(Room nextRoom);
        void printHistory() const;
};

#endif