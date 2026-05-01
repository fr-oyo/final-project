#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <vector>
using namespace std;

class Item {
public:
    string name;
    int effect;
    string type;

    Item(string n, int e, string t);
};

class Character {

protected:
    string Name;
    int Max_Health;
    int Current_Health;
    double Power;

    vector<Item> inventory;

public:
    Character(string n, int hp, double p);
    virtual ~Character();

    string getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    double getPower() const;

    bool isAlive() const;

    void takeDamage(int damage);
    void gainHealth(int amount);

    void addItem(const Item& item);
    void showInventory();
    int inventorySize() const;

    bool useItemOnTarget(int index, Character& target);
    int getTotalPower() const;

};

class Jess : public Character {
public:
    Jess();
};

class Bob : public Character {
public:
    Bob();
};

class Donut : public Character {
public:
    Donut();
};

class Jena : public Character {
public:
    Jena();
};

class Rylee : public Character {
public:
    Rylee();
};

#endif
