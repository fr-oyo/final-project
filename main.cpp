#include <iostream>
#include <cstdlib>
#include <ctime>

#include "dungeon.h"
using namespace std;

int main(){
    srand(time(0));
    Dungeon dungeon;
    char input;

    while (true){
        dungeon.printMap();

        cout << endl;
        cout << "";
        cin >> input;

        dungeon.movePlayer(input);
    }

    return 0;
}