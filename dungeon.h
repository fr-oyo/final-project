#ifndef DUNGEON_H
#define DUNGEON_H

#include "room.h"
#include <map>
#include <vector>
#include <utility>
using namespace std;

class Dungeon{
    private:
        static const int SIZE = 5;

        map<pair<int, int>, Room> dungeonMap;
        vector<Room> previousRooms;
        pair<int, int> currentPosition;
        int nextRoomId;

    public:
        Dungeon();
        ~Dungeon();

        void generateDungeon();
        void printMap() const;
        void printHistory() const;

        bool movePlayer(char direction);

    private:
        bool isValidPosition(int x, int y) const;
        bool roomExists(pair<int, int> position) const;

        RoomType getRandomRoomType() const;
        void connectRooms(pair<int, int> a, pair<int, int> b);
        void placeBossRoom();

        pair<int, int> getNeighborPosition(char direction) const;
        string getDisplayToken(const Room& room) const;
};

#endif