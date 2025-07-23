#include "potion.h"

#include <iostream>

#include "util.h"
#include "character.h"

using namespace std;

Potion::Potion():
    Item{} {}

std::unique_ptr<Potion> makePotion(Potion::PotionType type) {
}

HealthPotion::HealthPotion():
    Potion{} {}

AttackPotion::AttackPotion():
    Potion{} {}

DefensePotion::DefensePotion():
    Potion{} {}

PoisonPotion::PoisonPotion():
    Potion{} {}
    
WeakPotion::WeakPotion():
    Potion{} {}
     
BrittlePotion::BrittlePotion():
    Potion{} {}

char Potion::icon() const {
    return 'P';
}


void Potion::affect(Entity &) {
    getCout() << "THE POTION DOES NOTHING!!!!" << endl;
    getCout() << "I SHOULDN'T EXIST." << endl;
}

static const int DELTA_HP = 10;
static const int DELTA_ATK = 5;
static const int DELTA_DEF = DELTA_ATK;

void HealthPotion::affect(Entity &e) {
    try {
        Character &character {dynamic_cast<Character&>(e)};
        character.setHP(character.getHP() + DELTA_HP);
        setStatus(Entity::Status{
            .action = Entity::Action::KILL_ME,
            .data = monostate{},
        });
        notifyObservers();
    }
    catch(const bad_cast &ex) {}
}

void AttackPotion::affect(Entity &e) {
    try {
        Character &character {dynamic_cast<Character&>(e)};
        character.setATK(character.getATK() + DELTA_ATK);
        setStatus(Entity::Status{
            .action = Entity::Action::KILL_ME,
            .data = monostate{},
        });
        notifyObservers();
    }
    catch(const bad_cast &ex) {}
}

void DefensePotion::affect(Entity &e) {
    try {
        Character &character {dynamic_cast<Character&>(e)};
        character.setDEF(character.getDEF() + DELTA_DEF);
        setStatus(Entity::Status{
            .action = Entity::Action::KILL_ME,
            .data = monostate{},
        });
        notifyObservers();
    }
    catch(const bad_cast &ex) {}
}

void PoisonPotion::affect(Entity &e) {
    try {
        Character &character {dynamic_cast<Character&>(e)};
        character.setHP(max(1, character.getHP() - DELTA_HP));
        setStatus(Entity::Status{
            .action = Entity::Action::KILL_ME,
            .data = monostate{},
        });
        notifyObservers();
    }
    catch(const bad_cast &ex) {}
}

void WeakPotion::affect(Entity &e) {
    try {
        Character &character {dynamic_cast<Character&>(e)};
        character.setATK(max(0, character.getATK() - DELTA_ATK));
        setStatus(Entity::Status{
            .action = Entity::Action::KILL_ME,
            .data = monostate{},
        });
        notifyObservers();
    }
    catch(const bad_cast &ex) {}
}


void BrittlePotion::affect(Entity &e) {
    try {
        Character &character {dynamic_cast<Character&>(e)};
        character.setDEF(max(0, character.getDEF() - DELTA_DEF));
        setStatus(Entity::Status{
            .action = Entity::Action::KILL_ME,
            .data = monostate{},
        });
        notifyObservers();
    }
    catch(const bad_cast &ex) {}
}

// character.setHP(max(1, character.getHP() - 10));
