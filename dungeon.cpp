#include "dungeon.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cctype>
using namespace std;

Dungeon::Dungeon(){
    nextRoomId = 0;
    currentPosition = {2,2};
    //currentPositon = {int rand() % 5, rand() % 5};

    generateDungeon();
    dungeonMap[currentPosition].setVisited(true);
}

Dungeon::~Dungeon(){
    //empty...
}

bool Dungeon::isValidPosition(int x, int y) const{
    return x >= 0 && x < SIZE && y >= 00 && y < SIZE;
}
bool Dungeon::roomExists(pair<int, int> position) const{
    return dungeonMap.find(position) != dungeonMap.end();
}

RoomType Dungeon::getRandomRoomType() const{
    int random = rand() % 5;

    if (random == 0){
        return TREASURE;
    }
    else if (random == -1){
        return REST;
    }
    else{
        return DEFAULT;
    }
}

void Dungeon::generateDungeon(){
    dungeonMap.clear();
    previousRooms.clear();

    Room startRoom(START, nextRoomId++, 2, 2);
    dungeonMap[{2, 2}] = startRoom;
    currentPosition = {2, 2};

    vector<pair<int, int>> frontier;
    frontier.push_back({2, 2});

    int maxRooms = 15;

    while(!frontier.empty() && dungeonMap.size() < maxRooms){
        pair<int, int> current = frontier.back();
        frontier.pop_back();

        vector<pair<int, int>> directions = {
            {0,-1},
            {0, 1},
            {-1, 0},
            {1, 0}
        };

        for (int i = 0; i < directions.size(); i++){
            int newX = current.first + directions[i].first;
            int newY = current.second + directions[i].second;

            pair<int, int> newPosition = {newX, newY};

            if (!isValidPosition(newX, newY)) {
                continue;
            }
            if (roomExists(newPosition)){
                continue;
            }
            if (dungeonMap.size() >= maxRooms){
                break;
            }

            if (rand() % 100 < 55) {
                Room newRoom(getRandomRoomType(), nextRoomId++, newX, newY);
                dungeonMap[newPosition] = newRoom;
                connectRooms(current, newPosition);
                frontier.push_back(newPosition);
            }
        }
    }

    placeBossRoom();

}

void Dungeon::connectRooms(pair<int, int> a, pair<int, int> b){
    int ax = a.first;
    int ay = a.second;
    int bx = b.first;
    int by = b.second;

    if (bx == ax && by == ay - 1){
        dungeonMap[a].setUp(true);
        dungeonMap[b].setDown(true);
    }
    else if (bx == ax && by == ay + 1){
        dungeonMap[a].setDown(true);
        dungeonMap[b].setUp(true);
    }
    else if (bx == ax - 1 && by == ay){
        dungeonMap[a].setLeft(true);
        dungeonMap[b].setRight(true);
    }
    else if (bx == ax + 1 && by == ay){
        dungeonMap[a].setRight(true);
        dungeonMap[b].setLeft(true);
    }
}

void Dungeon::placeBossRoom(){
    pair<int, int> bossPosition = currentPosition;
    int farthest = -1;

    for (auto entry:dungeonMap){
        pair<int, int> position = entry.first;
        if (position == currentPosition){
            continue;
        }

        int distance = abs(position.first - 2) + abs(position.second - 2);
        if (distance > farthest){
            farthest = distance;
            bossPosition = position;
        }
    }

    dungeonMap[bossPosition].setType(BOSS);

}

pair <int, int> Dungeon::getNeighborPosition(char direction) const {
    int x = currentPosition.first;
    int y = currentPosition.second;

    direction = tolower(direction);

    if (direction == 'w'){
        return{x, y - 1};
    }
    else if(direction == 's'){
        return{x, y + 1};
    }
    else if(direction == 'a'){
        return{x - 1, y};
    }
    else if(direction == 'd'){
        return{x + 1, y};
    }

    return currentPosition;
}

bool Dungeon::movePlayer(char direction){
    direction = tolower(direction);

    Room& currentRoom = dungeonMap[currentPosition];
    bool canMove = false;

    if (direction == 'w' && currentRoom.hasUp()){
        canMove = true;
    }
    else if (direction == 's' && currentRoom.hasDown()){
        canMove = true;
    }
    else if (direction == 'a' && currentRoom.hasLeft()){
        canMove = true;
    }
    else if (direction == 'd' && currentRoom.hasRight()){
        canMove = true;
    }

    if (!canMove){
        cout << "You are unable to move that direction." << endl;
        return false;
    }

    pair<int, int> nextPosition = getNeighborPosition(direction);

    if (!roomExists(nextPosition)){
        cout << "There's no room that way!" << endl;
        return false;
    }

    previousRooms.push_back(currentRoom);

    currentPosition = nextPosition;
    dungeonMap[currentPosition].setVisited(true);

    return true;
}

string Dungeon::getDisplayToken(const Room& room) const{
    if (room.getId() == dungeonMap.at(currentPosition).getId()){
        return "[*]";
    }

    if (!room.isVisited()){
        return "[?]";
    }

    string token = "[";
    token += room.getSymbol();
    token += "]";
    return token;
}

void Dungeon::printMap() const{
    const Room& currentRoom = dungeonMap.at(currentPosition);

    pair<int, int> up = {currentPosition.first, currentPosition.second - 1};
    pair<int, int> down = {currentPosition.first, currentPosition.second + 1};
    pair<int, int> left = {currentPosition.first - 1, currentPosition.second};
    pair<int, int> right = {currentPosition.first + 1, currentPosition.second};

    string upToken = "   ";
    string downToken = "   ";
    string leftToken = "   ";
    string rightToken = "   ";

    if (currentRoom.hasUp() && roomExists(up)){
        upToken = getDisplayToken(dungeonMap.at(up));
    }
    if (currentRoom.hasDown() && roomExists(down)){
        downToken = getDisplayToken(dungeonMap.at(down));
    }

    if (currentRoom.hasLeft() && roomExists(left)){
        leftToken = getDisplayToken(dungeonMap.at(left));
    }

    if (currentRoom.hasRight() && roomExists(right)){
        rightToken = getDisplayToken(dungeonMap.at(right));
    }

    cout << endl;
    cout << "----- Current Map View -----" << endl;

    if (currentRoom.hasUp() && roomExists(up)) {
        cout << "      " << upToken << endl;
        cout << "       |" << endl;
    }

    cout << leftToken;

    if (currentRoom.hasLeft() && roomExists(left)) {
        cout << " - ";
    } else {
        cout << "   ";
    }

    cout << "[*]";

    if (currentRoom.hasRight() && roomExists(right)) {
        cout << " - ";
    } else {
        cout << "   ";
    }

    cout << rightToken << endl;

    if (currentRoom.hasDown() && roomExists(down)) {
        cout << "       |" << endl;
        cout << "      " << downToken << endl;
    }

    cout << endl;
    cout << "Pick where to go next with W A S D" << endl;
}

void Dungeon::printHistory() const {
    cout << endl;
    cout << "Visited room history:" << endl;

    for (int i = 0; i < previousRooms.size(); i++) {
        cout << previousRooms[i].getTypeName()
             << " at ("
             << previousRooms[i].getX()
             << ", "
             << previousRooms[i].getY()
             << ")"
             << endl;
    }
}