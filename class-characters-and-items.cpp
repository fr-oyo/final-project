#include <iostream>
#include <vector>
using namespace std;

// ================= ITEM =================
class Item {
public:
    string name;
    int effect;
    string type; // heal, damage, info

    Item(string n, int e, string t)
        : name(n), effect(e), type(t) {}
};

// ================= BASE CHARACTER =================
class Character {

protected:
    string Name;
    int Max_Health {0};
    int Current_Health {0};
    double Power_multipler {0.0};

    vector<Item> inventory;

    static int Character_alive;

public:
    Character(){
        Character_alive++;
    }

    Character(string name, int maxHealth, double power){
        Name = name;
        Max_Health = maxHealth;
        Current_Health = maxHealth;
        Power_multipler = power;
        Character_alive++;
    }

    virtual ~Character(){
        Character_alive--;
    }

    virtual void intro(){
        cout << "I am " << Name << endl;
    }

    string getName() const { return Name; }
    int gethealth() const { return Current_Health; }
    int getMaxHealth() const { return Max_Health; }
    double getPower() const { return Power_multipler; }

    static int Still_alive(){
        return Character_alive;
    }

    // ================= INVENTORY =================
    void addItem(const Item& item){
        inventory.push_back(item);
    }

    void showInventory() const{
        cout << "\n" << Name << "'s Inventory:\n";

        if (inventory.empty()){
            cout << "Empty\n";
            return;
        }

        for (int i = 0; i < inventory.size(); i++){
            cout << i << ": " << inventory[i].name
                 << " (" << inventory[i].type
                 << ", +" << inventory[i].effect << ")\n";
        }
    }

    // ================= ITEM USE =================
    void useItem(int index){
        if (index < 0 || index >= inventory.size()){
            cout << "Invalid item index.\n";
            return;
        }

        Item item = inventory[index];

        cout << "Using " << item.name << "...\n";

        if (item.type == "heal"){
            gainHealth(item.effect);
        }
        else if (item.type == "damage"){
            takeDamage(item.effect);
        }
        else {
            cout << "Nothing happens...\n";
        }

        inventory.erase(inventory.begin() + index);
    }

    // ================= COMBAT =================
    void takeDamage(int amount){
        Current_Health -= amount;

        if (Current_Health < 0)
            Current_Health = 0;

        cout << Name << " takes " << amount
             << " damage. HP: " << Current_Health
             << "/" << Max_Health << endl;
    }

    void gainHealth(int amount){
        if (amount <= 0){
            cout << "Invalid heal amount.\n";
            return;
        }

        Current_Health += amount;

        if (Current_Health > Max_Health)
            Current_Health = Max_Health;

        cout << Name << " healed. HP: "
             << Current_Health << "/"
             << Max_Health << endl;
    }
};

int Character::Character_alive = 0;

// ================= SUBCLASSES =================
class Jess : public Character {
public:
    Jess() : Character("Jess", 100, 3.2) {}

    void intro() override{
        cout << "Jess: balanced fighter.\n";
    }
};

class Bob : public Character {
public:
    Bob() : Character("Bob ", 60, 7.7) {}

    void intro() override{
        cout << "Bob: glass cannon.\n";
    }
};

class Donut : public Character {
public:
    Donut() : Character("Donut (the cat)", 5, 154.2) {}

    void intro() override{
        cout << "Donut: chaos entity.\n";
    }
};

// ================= MAIN =================
int main(){

    // ITEMS
    Item potion("Potion", 25, "heal");
    Item hot_potato("Hot Potato", 40, "damage");
    Item ring("Ring of Sight", 0, "info");

    // CHARACTER SELECTION
    Character* player = nullptr;

    cout << "Choose character:\n";
    cout << "1. Jess\n";
    cout << "2. Bob\n";
    cout << "3. Donut\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;

    if (choice == 1) player = new Jess();
    else if (choice == 2) player = new Bob();
    else if (choice == 3) player = new Donut();
    else {
        cout << "Invalid choice.\n";
        return 0;
    }

    player->intro();

    cout << "\nYou enter a dark dungeon...\n";

    // ================= GAME LOOP =================
    while (true){

        cout << "\n===== " << player->getName() << " MENU =====\n";
        cout << "HP: " << player->gethealth()
             << "/" << player->getMaxHealth() << endl;

        cout << "1. View Stats\n";
        cout << "2. View Inventory\n";
        cout << "3. Use Item\n";
        cout << "4. Add Potion\n";
        cout << "5. Add Hot Potato\n";
        cout << "6. Quit\n";
        //cout << "7. Quit\n";
        cout << "Choice: ";

        int action;
        cin >> action;

        if (action == 6){
            cout << "Exiting game...\n";
            break;
        }

        else if (action == 1){
            cout << "\nName: " << player->getName() << endl;
            cout << "Health: " << player->gethealth()
                 << "/" << player->getMaxHealth() << endl;
            cout << "Power: " << player->getPower() << endl;
        }

        else if (action == 2){
            player->showInventory();
        }

        else if (action == 3){
            player->showInventory();
            cout << "\nEnter item index: ";
            int index;
            cin >> index;
            player->useItem(index);
        }

        else if (action == 4){
            player->addItem(potion);
            cout << "Potion added!\n";
        }

        else if (action == 5){
            player->addItem(hot_potato);
            cout << "Hot Potato added!\n";
        }

       
        else {
            cout << "Invalid option.\n";
        }
    }

    delete player;

    cout << "\nCharacters alive: "
         << Character::Still_alive() << endl;

    return 0;
}
