#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;


class Item {
public:
    string name;
    int effect;
    string type; // "heal" or "damage"

    Item(string n, int e, string t) : name(n), effect(e), type(t) {}
};


class Character{ //this is the class defined
  

    private: //the private members that are read only
        string Name;
        int Health_Number {0};
        double Power_multipler {0.0};
        vector<Item> inventory; 

        static int Character_alive;

    public:
        Character(){ // this increments the count on objects by one every time an Character is established in main
            Character_alive++;
        };
        Character(const string& name, int health, double Power){ //this is a constructor, called by the class when an object is created, this is where to set defaults
            Name = name;
            Health_Number = health;
            Power_multipler = Power;
            Character_alive++;
        };



~Character(){ //deconstructor that decreases the count by 1
    Character_alive--;
}

string getName() const{ // this is an observer, or a 'getter' which reads private data safely
    return Name;
}

int gethealth() const{ 
    return Health_Number;
}

double getPower() const{
    return Power_multipler;
}

double total_damage_power() const{
    return (Health_Number * Power_multipler);
}

static int Still_alive(){
    return Character_alive;
}

void sethealth (int health){  //checks the constraints of health being above -1
    if ( health >= 0)
    Health_Number = health;
    else Health_Number = 0;
}

void setPower(double Power){ //checks the constraints of Power being above -1
    if(Power >= 0) {
        Power_multipler = Power;}
    else Power_multipler = 0;
}

 void addItem(const Item& item){
        inventory.push_back(item);
    }

    void showInventory() const {
        cout << Name << "'s Inventory:\n";

        if (inventory.empty()){
            cout << "  Empty\n";
            return;
        }

        for (int i = 0; i < inventory.size(); i++){
            cout << i << ": " << inventory[i].name
                 << " (" << inventory[i].type
                 << ", +" << inventory[i].effect << ")\n";
        }
    }

void printInventory() const{
    cout << Name << "'s Inventory: ";
    
    if (inventory.empty()){
        cout << "Empty";
    } else {
        for (const auto& item : inventory){
            cout << item.name << " ";
        }
    }
    cout << endl;
}

bool Heal(int amount){ // a function to call to ensure that when trying to Heal, you are paassing in a positive value
    if (amount > 0)
    {
        Health_Number += amount;
        return true;
    }
    else
    cout << "YOU'VE BEEN HEALED. +" << amount << " has been added to your health. Health is " << Health_Number << endl;
    return false;
}

bool damage(int amount){ // a function to call to ensure that when trying to damage, you are paassing in a value greater than 0 but smaller than the amount of items you currently have
    if (amount > 0 && amount < Health_Number){
        Health_Number -= amount;
        return true;
    }
    cout << "YOU HAVE DIED." << endl;
    return false;
}

};

void print(){ //print function for errors

    cout << "you entered an invalid input. Try again" << endl;
    
}

void printing(const Character& player_one, const Character& player_two, const Character& player_three){

    cout << "Name: " << player_one.getName() << endl;
    cout << "health: " << player_one.gethealth() << endl;
    cout << "Power: " << player_one.getPower()  << endl;
    cout << "Total damage power (when full health): " << player_one.total_damage_power() << endl;
    player_one.printInventory();
    cout << endl;

    cout << "Name: " << player_two.getName() << endl;
    cout << "health: " << player_two.gethealth() << endl;
    cout << "Power: " << player_two.getPower() << endl;
    cout << "Total damage power (when full health): " << player_two.total_damage_power() << endl;
    player_two.printInventory();
    cout << endl;

    cout << "Name: " << player_three.getName() << endl;
    cout << "health: " << player_three.gethealth() << endl;
    cout << "Power: " << player_three.getPower() << endl;
    cout << "Total damage power (when full health): " << player_three.total_damage_power() << endl;
    player_three.printInventory();
    cout << endl;

    //cout << "The final object count is: " << Character_alive << endl;
}

int Character::Character_alive = 0; // since this is a static data type, you need to have a memory location so this is establishing one

int main(){

    string answer;
    string itemname;
    string choice;
    int number;
    
   // cout <<"Objects created brefore establishing any in main: " << Character::Still_alive() << endl;

    Character player_one ("Jess", 100, 3.2); //creating object
    Character player_two ("Bob", 60, 5.7);
    Character player_three ("Donut", 5, 154.2);

    Item potion("Potion", 25, "heal");
    Item hot_potato("Extremely hot potato", 40, "damage");
    Item ring_of_sight("Ring of Sight", 0, "Information");


    // Give items
    player_one.addItem(potion);
    player_two.addItem(potion);
    player_one.addItem(hot_potato);


    cout << "Players available: '" <<  Character::Still_alive() << endl << endl;

    cout << "Current stats: " << endl << endl;
    printing( player_one, player_two, player_three);
    




    while (true){

        cout << "\n===== MENU =====\n";
        cout << "1. View Stats\n";
        cout << "2. Add Item to Player\n";
        cout << "3. View Inventory\n";
        cout << "4. Quit\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;

        cout << endl;

        if (choice == 4){
            cout << "Exiting game...\n";
            break;
        }

        // ================= VIEW STATS =================
        if (choice == 1){
            printing(player_one, player_two, player_three);
        }

        // ================= ADD ITEM =================
        else if (choice == 2){

            cout << "\nSelect player:\n";
            cout << "1. Jess\n";
            cout << "2. Bob\n";
            cout << "3. Donut the cat\n";
            cout << "Choice: ";

            int playerChoice;
            cin >> playerChoice;

            cout << "\nSelect item:\n";
            cout << "1. Potion\n";
            cout << "2. Hot Potato\n";
            cout << "3. Ring of Sight\n";
            cout << "Choice: " << endl;

            int itemChoice;
            cin >> itemChoice;

            Character* selectedPlayer = nullptr;
            Item* selectedItem = nullptr;

            // pick player
            if (playerChoice == 1) selectedPlayer = &player_one;
            else if (playerChoice == 2) selectedPlayer = &player_two;
            else if (playerChoice == 3) selectedPlayer = &player_three;
            else {
                cout << "Invalid player.\n";
                continue;
            }

            // pick item
            if (itemChoice == 1) selectedItem = &potion;
            else if (itemChoice == 2) selectedItem = &hot_potato;
            else if (itemChoice == 3) selectedItem = &ring_of_sight;
            else {
                cout << "Invalid item.\n";
                continue;
            }

            selectedPlayer->addItem(*selectedItem);

            cout << "Added " << selectedItem->name
                 << " to " << selectedPlayer->getName() << endl;
        }

        // ================= VIEW INVENTORY =================
        else if (choice == 3){

            cout << "\nSelect player:\n";
            cout << "1. Jess\n";
            cout << "2. Bob\n";
            cout << "3. Donut the cat\n";
            cout << "Choice: " << endl;

            int playerChoice;
            cin >> playerChoice;

            if (playerChoice == 1) player_one.showInventory();
            else if (playerChoice == 2) player_two.showInventory();
            else if (playerChoice == 3) player_three.showInventory();
            else cout << "Invalid player.\n";
        }

        else {
            cout << "Invalid menu choice.\n";
        }
    }

    return 0;
}
