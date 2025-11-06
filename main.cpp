#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <thread>

using namespace std;

// Superclass Character
class Character {
    // Atribut
    protected:
        string name;
        int _hp;
        int _mana;
        int _attack;
        int _defense;

    public:
        // Constructor
        Character(string charName, int healthPoints, int mana, int attackPower, int defensePower) : name(charName), _hp(healthPoints), _mana(mana), _attack(attackPower), _defense(defensePower){
        };

        // Display Character Information
        void display() {
            cout << "+----------------------------------------+" << endl;
            cout << "|          CHARACTER STATUS              |" << endl;
            cout << "+----------------------------------------+" << endl;
            cout << "| Name     : " << name << endl;
            cout << "| HP       : " << _hp << endl;
            cout << "| Mana     : " << _mana << endl;
            cout << "| Attack   : " << _attack << endl;
            cout << "| Defense  : " << _defense << endl;
            cout << "+----------------------------------------+" << endl;
        }

        // Getter

        int getHP(){
            return _hp;
        }

        string getName() {
            return name;
        }

        // === METHOD ===

        // Attack method
        void attack(Character &target)
        {
            cout << "> " << name << " attack " << target.name << " for " << _attack << " damage!" << endl;

            // Run the logic
            target.take_damage(_attack);
            // cout << target.name << " HP remaining: " << target._hp << endl;
        }

        // Take damage method
        void take_damage(int amount) {
            _hp -= amount;
            if (_hp < 0) {
                _hp = 0;
            }
            cout << " " << name << " takes " << amount << " damage. (HP: " << _hp << ")" << endl;
            // _defense -= 1;
            // if (_defense < 0) _defense = 0;
        }

        // Check is character still alive or not
        bool is_alive()
        {
            return _hp > 0;
        }
};

// Subclass for Player
class Player : public Character {
    public:
        Player(string charName, int healthPoints, int mana, int attackPower, int defensePower) : Character(charName, healthPoints, mana, attackPower, defensePower){
            cout << "\n[PLAYER READY] " << charName << " joins the adventure!" << endl;
        };
};

class Enemy : public Character {
    public:
        Enemy(string charName, int healthPoints, int mana, int attackPower, int defensePower) : Character(charName, healthPoints, mana, attackPower, defensePower) {
            cout << "\n[ENEMY ENCOUNTER] A wild " << charName << " appears!" << endl;
        }
};

void battle(Player &player, Enemy &enemy) {
    cout << "\n========================================" << endl;
    cout << "              BATTLE START!              " << endl;
    cout << "========================================" << endl;

    while (player.is_alive() && enemy.is_alive()) {
        int choice;

        cout << "\nYour turn, " << player.getName() << "!" << endl;
        cout << "1. Basic Attack" << endl;
        cout << "2. Ability (not implemented)" << endl;
        cout << "Choose action (1/2): ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "\nYou use Basic Attack!" << endl;
            player.attack(enemy);
        } else if (choice == 2 ) {
            cout << "\nYou use your ability" << endl;
        } else {
            cout << "Invalid input, try again!" << endl;
            continue;
        }

        if (enemy.is_alive()) {
           cout << "\n--- Enemy Turn ---" << endl;
            enemy.attack(player);
        }
    }

    cout << "\n========================================" << endl;
    if (player.is_alive()) {
        cout << "Victory! You defeated " << enemy.getName() << "!" << endl;
    } else {
        cout << "You were defeated by " << enemy.getName() << "..." << endl;
    }
    cout << "========================================" << endl;
    cout << "Press Enter to continue..." << endl;
    cin.ignore();
    cin.get();
}

int main() {
    // Player Initialization
    
    cout << "========================================" << endl;
    cout << "        TEXT RPG: THE ADVENTURE          " << endl;
    cout << "========================================" << endl;

    Player player("Faradis", 100, 20, 20, 5);
    player.display();

    cout << "Press Enter to begin your journey..." << endl;
    cin.get();

    int steps = 0;

    int attack;

    while (player.is_alive()) {
            steps ++;
            cout << "Step: " << steps << ": You walk forward..." << endl;

            if (steps % 3 == 0 && steps % 5 != 0 && steps < 100 && steps > 0 && player.is_alive()) {
                cout << "\nYou feel something lurking nearby..." << endl;
                
                // Enemy Initialization
                string enemy[4] = {"Slime", "Goblin", "Skeleton", "wolf"};
                int index = rand() % 4;
                int hp = rand() % 10 + 20;
                int att = rand() % 10 + 20;

                Enemy enemyEncounter(enemy[index], hp, 0, att, 0);
                enemyEncounter.display();

                cout << "Press Enter to battle!" << endl;
                cin.get();

                battle(player, enemyEncounter);
        }
    }

    cout << "\n========================================" << endl;
    cout << "   Your journey has come to an end...    " << endl;
    cout << "========================================" << endl;

    return 0;
}