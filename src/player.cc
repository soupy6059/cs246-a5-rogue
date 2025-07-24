#include "player.h"

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <cassert>
#include <memory>
#include <races.h>
#include <rng.h>

#include "log.h"

using namespace std;

Player::Player(CharacterDefaults d): Character{d} {
    defaults.atk = d.atk;
    defaults.def = d.def;
    defaults.hp = d.hp;
    defaults.acc = d.hp;
}


void Player::appendVerb(Verb::Status newStatus) {
    verb.appendStatus(newStatus);
}

Verb &Player::refVerb() {
    return verb;
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

string Player::icon() const {
    return "\033[94;1m@\033[0m";
}

void Player::setHP(int n) {if (n > defaults.hp) hp = defaults.hp;}

void Player::setDEF(int n) {if (n <= 0) def = 1;}

void Player::setATK(int n) {if (n <= 0) atk = 1;}

void Player::attack(Tile& target) {
    std::shared_ptr<Halfling> h = std::dynamic_pointer_cast<Halfling>(target.getEntity());
    if (h) {
        int r = getRand(0, 2);
        if (r) {
            Character::attack(target);
        }
    } else {
        Character::attack(target);
    }
}
