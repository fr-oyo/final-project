class Enemy {
protected:
    string name;
    int health;
    int damage;

public:
    Enemy(string n, int h, int d)
        : name(n), health(h), damage(d) {}

    virtual ~Enemy() {}

    string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    bool isAlive() const {
        return health > 0;
    }

    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }

    int getDamage() const {
        return damage;
    }
};


#include <cstdlib>
#include <iostream>
using namespace std;

class Stalker : public Enemy {
private:
    string hiddenSide;

public:
    Stalker() : Enemy("Stalker", 40, 7) {
        hiddenSide = (rand() % 2 == 0) ? "left" : "right";
    }

    void encounter(Character &player) {

        cout << "\nYou feel something watching you...\n";
        cout << "Look left or right: ";

        string guess;
        cin >> guess;

        // ❌ Wrong guess = immediate punishment
        if (guess != hiddenSide) {
            cout << "Wrong direction! The Stalker strikes!\n";
            player.damage(damage);
            return;
        }

        cout << "You found the Stalker! Combat begins!\n";

        // ⚔️ Combat loop
        while (isAlive() && player.gethealth() > 0) {

            string action;
            cout << "\nType 'attack': ";
            cin >> action;

            if (action == "attack") {

                int roll = rand() % 100; // 0–99

                // 70% hit chance
                if (roll < 70) {
                    int playerDamage = player.total_damage_power();

                    cout << "You hit the Stalker for " 
                         << playerDamage << " damage!\n";

                    takeDamage(playerDamage);

                    if (!isAlive()) {
                        cout << "\nCongrats! You beat the Stalker!\n";
                        return;
                    }

                }
                //30% miss chance → Stalker attacks
                else {
                    cout << "You missed! The Stalker counterattacks!\n";
                    player.damage(damage);
                }

            } else {
                cout << "You hesitate... The Stalker attacks!\n";
                player.damage(damage);
            }
        }
    }
};

class Goblin : public Enemy {
public:
    Goblin() : Enemy("Goblin", 30, 5) {}

    void encounter(Character &player) {

        cout << "\nA Goblin runs at you from the front!\n";

        // ⚔️ Combat loop
        while (isAlive() && player.gethealth() > 0) {

            string action;
            cout << "\nType 'attack': ";
            cin >> action;

            if (action == "attack") {

                int roll = rand() % 100; // 0–99

                // 🟢 80% chance to hit
                if (roll < 80) {
                    int playerDamage = player.total_damage_power();

                    cout << "You hit the Goblin for "
                         << playerDamage << " damage!\n";

                    takeDamage(playerDamage);

                    if (!isAlive()) {
                        cout << "\nYou defeated the Goblin!\n";
                        return;
                    }
                }
                // 🔴 20% miss → Goblin attacks
                else {
                    cout << "You missed!\n";
                    cout << "The Goblin throws a pot of soup at you!\n";
                    player.damage(damage);
                }

            } else {
                cout << "You hesitate!\n";
                cout << "The Goblin throws a pot of chili at you!\n";
                player.damage(damage);
            }
        }
    }
};
