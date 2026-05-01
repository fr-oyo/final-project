class Combat {
public:

    static void fight(Character &player, Enemy &enemy) {

        cout << "\nA wild " << enemy.getName() << " appears!\n";

        while (enemy.isAlive() && player.gethealth() > 0) {

            string action;
            cout << "\nType 'attack': ";
            cin >> action;

            if (action == "attack") {

                int roll = rand() % 100;

                // Player hits
                if (roll < 75) {

                    double player_damage = player.total_power();

                    cout << "You hit the " << enemy.getName()
                         << " for " << player_damage << " damage!\n";

                    enemy.takeDamage(player_damage);

                    if (!enemy.isAlive()) {
                        cout << enemy.getName() << " defeated!\n";
                        return;
                    }

                } 
                // Player misses
                else {
                    cout << "You missed!\n";

                    int player_damage = enemy.getDamage();
                    player.takeDamage(player_damage);

                    cout << "You took " << player_damage << " damage!\n";
                }
            }

            else {
                cout << "You hesitate...\n";

                int player_damage = enemy.getDamage();
                player.takeDamage(player_damage);
            }
        }
    }
};


#include <iostream>
#include <string>
using namespace std;

class Character; // forward declaration

class Enemy {
protected:
    string name;
    int health;
    int damage;

public:
    Enemy(string n, int h, int d)
        : name(n), health(h), damage(d) {}

    virtual ~Enemy() {}

    // =========================
    // BASIC INFO
    // =========================
    string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    bool isAlive() const {
        return health > 0;
    }

    int getDamage() const {
        return damage;
    }

    // =========================
    // CORE MECHANICS
    // =========================
    virtual void takeDamage(double amount) {
        health -= amount;

        if (health < 0)
            health = 0;
    }

    // =========================
    // POLYMORPHIC ENCOUNTER
    // =========================
    virtual void encounter(Character &player) {
        cout << "An enemy appears: " << name << endl;
    }
};




class Stalker : public Enemy {
private:
    string hiddenSide;

public:
    Stalker() : Enemy("Stalker", 40, 7) {
        hiddenSide = (rand() % 2 == 0) ? "left" : "right";
    }

    bool find(Character &player) {

        string guess;

        while (true) {

            cout << "Look left or right: ";
            cin >> guess;

            if (guess != hiddenSide) {

                cout << "Wrong! The Stalker strikes!\n";
                player.takeDamage(damage);

                hiddenSide = (rand() % 2 == 0) ? "left" : "right";
            }
            else {
                cout << "You found the Stalker!\n";
                return true;
            }
        }
    }

    void encounter(Character &player) {

        cout << "\nA chilling presence surrounds you...\n";

        // 👁️ EVENT PHASE
        if (!find(player)) return;

        // ⚔️ COMBAT PHASE
        Combat::fight(player, *this);
    }
};



class Goblin : public Enemy {
public:
    Goblin() : Enemy("Goblin", 30, 5) {}

    void encounter(Character &player) {
        Combat::fight(player, *this);
    }
};



class Reese : public Enemy {
public:
    Reese() : Enemy("Reese", 1, 9) {}

    void encounter(Character &player) override {

        cout << "\nYou hear a loud buzzing noise...\n";
        cout << "Reese is coming in on a scooter at full speed!\n";

        cout << "Type 'dodge': ";
        string action;
        cin >> action;

        int roll = rand() % 100;

        // ❌ fail dodge OR wrong input
        if (action != "dodge" || roll >= 40) {

            cout << "Too slow! You get run over!\n";

            int player_damage = 9;
            player.takeDamage(player_damage);

            cout << "You lost " << player_damage << " HP!\n";
        }
        // ✔ success
        else {
            cout << "You dodged! Reese crashes into a wall and bursts into flames!\n";
        }
    }
};
