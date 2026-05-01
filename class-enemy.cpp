class Enemy {
protected:
    string name;
    int health;
    int damage;

public:
    Enemy(string n, int h, int d)
        : name(n), health(h), damage(d) {}

    virtual ~Enemy() {}

    string getName() const { return name; }

    int getHealth() const { return health; }

    bool isAlive() const { return health > 0; }

    void takeDamage(double dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }

    int getDamage() const { return damage; }
};

#include <iostream>
#include <cstdlib>
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

        string guess;

        // =========================
        // 👁️ GUESS LOOP
        // =========================
        while (true) {

            cout << "Look left or right: ";
            cin >> guess;

            if (guess != hiddenSide) {

                cout << "Wrong direction! The Stalker strikes!\n";

                int player_damage = damage;
                player.takeDamage(player_damage);

                cout << "You lost " << player_damage << " HP!\n";

                // reroll position
                hiddenSide = (rand() % 2 == 0) ? "left" : "right";

                cout << "The Stalker moves... try again.\n";
            }
            else {
                cout << "You found the Stalker! Combat begins!\n";
                break;
            }
        }

        // =========================
        // ⚔️ COMBAT LOOP
        // =========================
        while (isAlive() && player.gethealth() > 0) {

            string action;
            cout << "\nType 'attack': ";
            cin >> action;

            if (action == "attack") {

                int roll = rand() % 100;

                if (roll < 70) {

                    double player_damage = player.total_power();

                    cout << "You hit the Stalker for "
                         << player_damage << " damage!\n";

                    takeDamage(player_damage);

                    if (!isAlive()) {
                        cout << "\nCongrats! You beat the Stalker!\n";
                        return;
                    }
                }
                else {
                    cout << "You missed! The Stalker counterattacks!\n";

                    int player_damage = damage;
                    player.takeDamage(player_damage);

                    cout << "You lost " << player_damage << " HP!\n";
                }
            }
            else {
                cout << "You hesitate... The Stalker attacks!\n";

                int player_damage = damage;
                player.takeDamage(player_damage);

                cout << "You lost " << player_damage << " HP!\n";
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

                    double player_damage = player.total_power();

                    cout << "You hit the Goblin for "
                         << player_damage << " damage!\n";

                    takeDamage(player_damage);

                    if (!isAlive()) {
                        cout << "\nYou defeated the Goblin!\n";
                        return;
                    }
                }
                else {
                    cout << "You missed!\n";
                    cout << "The Goblin throws a pot of soup at you!\n";

                    int player_damage = damage;
                    player.takeDamage(player_damage);

                    cout << "You lost " << player_damage << " HP!\n";
                }
            }
            else {
                cout << "You hesitate!\n";
                cout << "The Goblin throws soup at you!\n";

                int player_damage = damage;
                player.takeDamage(player_damage);

                cout << "You lost " << player_damage << " HP!\n";
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

        if (action != "dodge" || roll >= 40) {

            cout << "Too slow! You get run over!\n";

            int player_damage = 9;
            player.takeDamage(player_damage);

            cout << "You lost " << player_damage << " HP!\n";
            return;
        }

        cout << "You dodged! Reese crashes and explodes!\n";
    }
};
