#include "player.h"

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cassert>

#include "log.h"

using namespace std;

Player::Player(CharacterDefaults d):
    Character{d.atk, d.def, d.hp, d.acc}, gold{d.gold} {}

void Player::setGold(int newGoldCount) {
    gold = newGoldCount;
}
int Player::getGold() const {
    return gold;
}

static const map<string,Direction> dirNameToDir {
    {"no",Direction::NORTH},
    {"so",Direction::SOUTH},
    {"ea",Direction::EAST},
    {"we",Direction::WEST},
    {"ne",Direction::NORTHEAST},
    {"nw",Direction::NORTHWEST},
    {"sw",Direction::SOUTHWEST},
    {"se",Direction::SOUTHEAST},
};
void Player::step() {
    string line, word;
    getline(cin, line);
    stringstream lineStream {line};
    lineStream >> word;

    // debug
    int thingsTried = 0;

    // MOVEMENT
    try{
        Direction dir {dirNameToDir.at(word)};
        setStatus(Entity::Status{
            .action = Entity::Action::MOVE,
            .data = dir,
        });
        ++thingsTried;
    }
    catch(...) {}

    // INTERACT
    if(word == "u") {
        try {
            lineStream >> word;
            Direction dir {dirNameToDir.at(word)};
            setStatus(Entity::Status{
                .action = Entity::Action::INTERACT,
                .data = dir,
            });
            ++thingsTried;
        }
        catch(...) {}
    }
    
    // ATTACK
    if(word == "a") {
        try {
            lineStream >> word;
            Direction dir {dirNameToDir.at(word)};
            setStatus(Entity::Status{
                .action = Entity::Action::ATTACK,
                .data = dir,
            });
            ++thingsTried;
        }
        catch(...) {}
    }
    
    assert(thingsTried == 0 || thingsTried == 1);
    if(thingsTried == 0) return;

    notifyObservers();
}

char Player::icon() const {
    return '@';
}

void Player::setHP(int n) {if (n > defaults.hp) hp = defaults.hp;}

void Player::setDEF(int n) {if (n <= 0) def = 1;}

void Player::setATK(int n) {if (n <= 0) atk = 1;}

void Player::attack(Tile& target) {
    Character::attack(target);
}
