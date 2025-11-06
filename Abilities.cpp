#include <iostream>
#include <string>

using namespace std;

// Superclass Character
class Character {
public:
    string name;
    int _hp;
    int _mana;
    int _attack;
    int _deffense;

public:
    Character(string charName, int healthPoints, int mana, int attackPower, int defensePower)
        : name(charName), _hp(healthPoints), _mana(mana), _attack(attackPower), _deffense(defensePower) {}

    void display() {
        cout << "\n================ CHARACTER STATUS ================" << endl;
        cout << " Name     : " << name << endl;
        cout << " HP       : " << _hp << endl;
        cout << " Mana     : " << _mana << endl;
        cout << " Attack   : " << _attack << endl;
        cout << " Defense  : " << _deffense << endl;
        cout << "====================================================\n" << endl;
    }

    int getHP() {
        return _hp;
    }

    void attack(Character &target) {
        cout << name << " attack " << target.name << " for " << _attack << " damage!" << endl;
        target.take_damage(_attack);
        cout << target.name << " HP remaining: " << target._hp << endl;
    }

    void take_damage(int amount) {
        _hp -= amount;
        if (_hp < 0) _hp = 0;
    }

    bool is_alive() {
        return _hp > 0;
    }
};

// Ability: FireBlast
class FireBlast {
public:
    int manaCost = 10;
    int usesLeft = 3;


    
    void use(Character &caster, Character &target) {
        if (caster._mana < manaCost) {
            cout << caster.name << " does not have enough mana to use FireBlast!" << endl;
            return;
        }

        if (usesLeft <= 0) {
            cout << "FireBlast has no uses left!" << endl;
            return;
        }

        int damage = caster._attack * 1.5;
        cout << caster.name << " casts FireBlast on " << target.name << "!" << endl;

        target.take_damage(damage);
        caster._mana -= manaCost;
        usesLeft--;

        cout << "Mana left: " << caster._mana << endl;
        cout << "FireBlast uses remaining: " << usesLeft << endl;
    }
};

// Ability: Heal
class Heal {
public:
    int manaCost = 20;

    void use(Character &caster) {
        if (caster._mana < manaCost) {
            cout << caster.name << " does not have enough mana to Heal!" << endl;
            return;
        }

        // Heal only allowed if HP <= 30%
        if ((float)caster._hp / 100.0f > 0.30f) {
            cout << caster.name << " cannot use Heal (HP is above 30%)!" << endl;
            return;
        }

        int healAmount = caster._attack * 0.8;
        caster._hp += healAmount;
        if (caster._hp > 100) caster._hp = 100;

        caster._mana -= manaCost;

        cout << caster.name << " used Heal and restored " << healAmount << " HP!" << endl;
        cout << "Current HP: " << caster._hp << endl;
        cout << "Mana left: " << caster._mana << endl;
    }
};

// Subclass for Player
class Player : public Character {
public:
    Player(string charName, int healthPoints, int mana, int attackPower, int defensePower)
        : Character(charName, healthPoints, mana, attackPower, defensePower) {
        cout << "Player named " << charName << " is generated!" << endl;
    }
};

// Subclass for Enemy
class Enemy : public Character {
public:
    Enemy(string charName, int healthPoints, int mana, int attackPower, int defensePower)
        : Character(charName, healthPoints, mana, attackPower, defensePower) {
        cout << "Enemy named " << charName << " is generated!" << endl;
    }
};

int main() {

    Player player1("Faradis", 100, 20, 20, 20);
    player1.display();

    // Create abilities ONCE
    FireBlast fire;
    Heal heal;

    int steps = 0;
    int attack;

    while (true) {
        steps += 1;
        if (steps % 3 == 0 && steps % 5 != 0 && steps < 100 && steps > 0 && player1.is_alive()) {

            cout << "You have already walked " << steps << " steps and found a monster" << endl;

            string enemy[4] = { "Slime", "Goblin", "Skeleton", "Wolf" };
            int index = rand() % 4;
            int hp = rand() % 10 + 20;
            int att = rand() % 10 + 20;
            Enemy slime(enemy[index], hp, 0, att, 0);
            slime.display();

            while (true) {

                if (!player1.is_alive()) {
                    cout << "Player is dead!" << endl;
                    break;
                }

                if (!slime.is_alive()) {
                    cout << "Enemy defeated!" << endl;
                    break;
                }

                cout << "====================" << endl;
                cout << "Choose your attack!" << endl;
                cout << "1. Basic Attack" << endl;
                cout << "2. Ability " << endl;
                cout << "====================" << endl;

                cout << "Choose your attack : ";
                cin >> attack;

                if (attack == 1) {
                    cout << "You choose basic attack" << endl;
                    player1.attack(slime);
                }
                else if (attack == 2) {
                    cout << "You use your ability" << endl;

                    cout << "\n=== Choose Ability ===" << endl;
                    cout << "1. FireBlast" << endl;
                    cout << "2. Heal" << endl;
                    cout << "Your choice: ";

                    int abilityChoice;
                    cin >> abilityChoice;

                    if (abilityChoice == 1) fire.use(player1, slime);
                    else if (abilityChoice == 2) heal.use(player1);
                    else cout << "Invalid choice!" << endl;
                }

                if (slime.getHP() > 0) slime.attack(player1);
            }
        }
    }

    return 0;
}
