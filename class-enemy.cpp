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

        if (guess != hiddenSide) {
            cout << "Wrong direction! The Stalker strikes!\n";
            player.takeDamage(damage);
            return;
        }

        cout << "You found the Stalker! Combat begins!\n";

        while (isAlive() && player.gethealth() > 0) {

            string action;
            cout << "\nType 'attack': ";
            cin >> action;

            if (action == "attack") {

                int roll = rand() % 100;

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
                else {
                    cout << "You missed! The Stalker counterattacks!\n";
                    player.takeDamage(damage);
                }
            }
            else {
                cout << "You hesitate... The Stalker attacks!\n";
                player.takeDamage(damage);
            }
        }
    }
};

class Goblin : public Enemy {
public:
    Goblin() : Enemy("Goblin", 30, 5) {}

    void encounter(Character &player) {

        cout << "\nA Goblin runs at you from the front!\n";

        while (isAlive() && player.gethealth() > 0) {

            string action;
            cout << "\nType 'attack': ";
            cin >> action;

            if (action == "attack") {

                int roll = rand() % 100;

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
                else {
                    cout << "You missed!\n";
                    cout << "The Goblin throws a pot of soup at you!\n";
                    player.takeDamage(damage);
                }

            } else {
                cout << "You hesitate!\n";
                cout << "The Goblin throws a pot of chili at you!\n";
                player.takeDamage(damage);
            }
        }
    }
};


class Reese : public Enemy {
public:
    Reese() : Enemy("Reese", 1, 9) {}

    void encounter(Character &player) {

        cout << "\nReese is riding a scooter at full speed!\n";
        cout << "Type 'dodge': ";

        string action;
        cin >> action;

        int roll = rand() % 100;

        // fail dodge OR wrong input
        if (action != "dodge" || roll >= 40) {

            cout << "You get run over!\n";
            player.takeDamage(9);

            cout << "You lost 9 HP!\n";
            return;
        }

        cout << "You dodged! Reese crashes and explodes!\n";
    }
};
