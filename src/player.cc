#include "player.h"

#include <iostream>

#include "log.h"

using namespace std;

Player::Player(const Entity::EntityImpl data, int atk, int def, int hp, int acc):
    Character{data, atk, def, hp, acc} {
        defaults.atk = atk;
        defaults.def = def;
        defaults.hp = hp;
        defaults.acc = acc;
    }

void Player::setGold(int newGoldCount) {
    gold = newGoldCount;
}
int Player::getGold() const {
    return gold;
}

void Player::step() {
    char input;
    // PLEASE SOMEONE FIX THIS, I CANT AND GOT ANNOYED
BADINPUT:
    cin >> input;
    if(!cin) {
        cin.clear();
        cin.ignore();
        goto BADINPUT;
    }
    switch(input) {
    case 'w':
        setStatus(Entity::Status{
            .action = Entity::Action::MOVE,
            .data = Direction::NORTH,
        });
        break;
    case 's':
        setStatus(Entity::Status{
            .action = Entity::Action::MOVE,
            .data = Direction::SOUTH,
        });
        break;
    case 'a':
        setStatus(Entity::Status{
            .action = Entity::Action::MOVE,
            .data = Direction::WEST,
        });
        break;
    case 'd':
        setStatus(Entity::Status{
            .action = Entity::Action::MOVE,
            .data = Direction::EAST,
        });
        break;
    default:
        cout << "Do better. WASD" << endl;
        goto BADINPUT;
        break;
    }
    Log::getLogFile("bug") << "notifyObservers() called from Player::step()" << endl;
    notifyObservers();
}

char Player::icon() const {
    return '@';
}
