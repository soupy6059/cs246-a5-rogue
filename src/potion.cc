#include "potion.h"

#include <iostream>

#include "util.h"
#include "character.h"

using namespace std;

Potion::Potion():
    Item{} {}

shared_ptr<Potion> Potion::makePotion(Potion::PotionType type) {
    switch (type) {
        case PotionType::HEALTH:
            return make_shared<HealthPotion>();
        case PotionType::ATTACK:
            return make_shared<AttackPotion>();
        case PotionType::DEFENSE:
            return make_shared<DefensePotion>();
        case PotionType::POISON:
            return make_shared<PoisonPotion>();
        case PotionType::WEAK:
            return make_shared<WeakPotion>();
        case PotionType::BRITTLE:
            return make_shared<BrittlePotion>();
        default: // Should be unreachable.
            return make_shared<HealthPotion>();
    }
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

string HealthPotion::getName() const { return "BH"; }
string AttackPotion::getName() const { return "BA"; }
string DefensePotion::getName() const { return "BD"; }
string PoisonPotion::getName() const { return "LH"; }
string WeakPotion::getName() const { return "LA"; }
string BrittlePotion::getName() const { return "LD"; }

string Potion::icon() const {
    return "\033[92;1mP\033[0m";
}


// void Potion::affect(Entity &) {
//     getCout() << "THE POTION DOES NOTHING!!!!" << endl;
//     getCout() << "I SHOULDN'T EXIST." << endl;
// }

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
        character.changeDeltaATK(DELTA_ATK);
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
        character.changeDeltaDEF(DELTA_DEF);
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
        int delta = character.getATK() - max(0, character.getATK() - DELTA_ATK);
        character.changeDeltaATK(-delta);
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
        int delta = character.getDEF() - max(0, character.getDEF() - DELTA_DEF);
        character.changeDeltaDEF(-delta);
        setStatus(Entity::Status{
            .action = Entity::Action::KILL_ME,
            .data = monostate{},
        });
        notifyObservers();
    }
    catch(const bad_cast &ex) {}
}

// character.setHP(max(1, character.getHP() - 10));
