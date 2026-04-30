#include <iostream>
#include <string>
using namespace std;

class Enemy {
protected:
    string name;
    int health;
    int attack;

public:
    // Constructor
    Enemy(string n, int h, int a) : name(n), health(h), attack(a) {}

    // Virtual destructor (important for inheritance!)
    virtual ~Enemy() {}

    // Basic attack behavior
    virtual void attackPlayer() {
        cout << name << " attacks for " << attack << " damage!\n";
    }

    // Virtual special ability (default = none)
    virtual void specialAbility() {
        cout << name << " has no special ability.\n";
    }

    // Take damage
    void takeDamage(int dmg) {
        health -= dmg;
        cout << name << " takes " << dmg << " damage!\n";
    }

    // Check if alive
    bool isAlive() const {
        return health > 0;
    }

    // Getter
    string getName() const {
        return name;
    }
};
