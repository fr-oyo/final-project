
#include <iostream>
#include <vector>
using namespace std;
// ================= ITEM =================
class Item {
public:
    string name;
    int effect;
    string type;

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
    Jess() : Character("Jess", 100, 0.17) {}

    void intro() override{
        cout << "Jess; the balanced fighter. You are well-built, a fighter equal in strenght and smarts.\n";
        cout << "You are the most resilient of the group, but does that mean you'll be the one to make it out?\n";

    }
};

class Bob : public Character {
public:
    Bob() : Character("Bob", 80, 0.23) {}

    void intro() override{
        cout << "Bob, a man of great power. You have immense power, power not to be trifled with.\n";
        cout << "It will be difficult to strike you down. Are you strong enough to stay stand though?\n";

    }
};

class Donut : public Character {
public:
    Donut() : Character("Donut", 40, 0.7) {}

    void intro() override{
        cout << "Donut. You are Donut. Donut the cat.\n";
        cout << "You are weak in health. On the last of your nine lives.\n";
        cout << "But your power is other-worldly. Unmatched...\n";
        cout << "But, for as much power as you hold, your extreme weakness keeps you always on deaths door.\n";
    }
};

class Jena : public Character {
public:
    Jena() : Character("Jena",55, 0.2) {}

    void intro() override{
        cout << "You are Jena.\n";
        cout << "Jena, while slightly weak in health holds steady against most opponents.\n";
        cout << "You're also very good-looking...but thats irrelevant.\n";
        cout << "If good at decision making, this should be a breeze...\n";
        cout << "Or, maybe not...\n";
    }
};

class Rylee : public Character {
public:
    Rylee() : Character("Rylee", 200, 0.01) {}

    void intro() override{
        cout << "People know you as Rylee.\n";
        cout << "Dear god you're weak. Like, really weak.\n";
        cout << "You have the best health, it'll take a thousand hits to take you down...\n";
        cout << "But, you are so so weak, people laugh at you, you're so weak...\n";
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

    cout << "Choose character (type the number):\n";
    cout << "1. Jess\n";
    cout << "2. Bob\n";
    cout << "3. Donut\n";
    cout << "4. Jena\n";
    cout << "5. Rylee\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;

    if (choice == 1) player = new Jess();
    else if (choice == 2) player = new Bob();
    else if (choice == 3) player = new Donut();
    else if (choice == 4) player = new Jena();
    else if (choice == 5) player = new Rylee();
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
