#include "character.h"

// character constructor
Item::Item(string n, int e, string t)
    : name(n), effect(e), type(t) {}

// character constructor
Character::Character(string n, int hp, double p)
    : Name(n), Max_Health(hp), Current_Health(hp), Power(p) {}

Character::~Character() {}

string Character::getName() const { return Name; }
int Character::getHealth() const { return Current_Health; }
int Character::getMaxHealth() const { return Max_Health; }
double Character::getPower() const { return Power; }

bool Character::isAlive() const { return Current_Health > 0; }


//updates health on if damage was taken
void Character::takeDamage(int damage){
    Current_Health -= damage;
    if (Current_Health < 0) Current_Health = 0;

    cout << Name << " HP: " << Current_Health << "/" << Max_Health << endl;
}

//updates health on if healing was taken
void Character::gainHealth(int amount){
    Current_Health += amount;
    if (Current_Health > Max_Health)
        Current_Health = Max_Health;

    cout << Name << " HP: " << Current_Health << "/" << Max_Health << endl;
}

void Character::addItem(const Item& item){
    inventory.push_back(item);
}

void Character::showInventory(){
    if (inventory.empty()){
        cout << "Inventory empty\n";
        return;
    }

    for (int i = 0; i < inventory.size(); i++){
        cout << i << ": " << inventory[i].name
             << " (" << inventory[i].type
             << ", +" << inventory[i].effect << ")\n";
    }
}

int Character::inventorySize() const{
    return inventory.size();
}

bool Character::useItemOnTarget(int index, Character& target){

    if (index < 0 || index >= inventory.size()){
        cout << "Invalid item.\n";
        return false;
    }

    Item item = inventory[index];

    cout << "Using " << item.name << "...\n";

    if (item.type == "heal")
        target.gainHealth(item.effect);
    else if (item.type == "damage")
        target.takeDamage(item.effect);

    inventory.erase(inventory.begin() + index);
    return true;
}
int Character::getTotalPower() const {
    double healthRatio = (double)Current_Health / (double)Max_Health;
    return (int)(Power * healthRatio * 10);
}
//character definition
Jess::Jess()
    : Character("Jess", 100, 0.17) {}

Bob::Bob()
    : Character("Bob", 80, 0.23) {}

Donut::Donut()
    : Character("Donut", 40, 0.7) {}

Jena::Jena()
    : Character("Jena",55, 0.2) {}

Rylee::Rylee() 
    : Character ("Rylee", 200, 0.01){}
