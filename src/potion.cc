#include "potion.h"

#include <iostream>

#include "util.h"
#include "character.h"
#include "races.h"

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

bool HealthPotion::known = false;
bool AttackPotion::known = false;
bool DefensePotion::known = false;
bool PoisonPotion::known = false;
bool WeakPotion::known = false;
bool BrittlePotion::known = false;

bool HealthPotion::getKnown() const {
    return HealthPotion::known;
}

void HealthPotion::setKnown(bool newKnown) {
    HealthPotion::known = newKnown;
}
bool AttackPotion::getKnown() const {
    return AttackPotion::known;
}

void AttackPotion::setKnown(bool newKnown) {
    AttackPotion::known = newKnown;
}

bool DefensePotion::getKnown() const {
    return DefensePotion::known;
}

void DefensePotion::setKnown(bool newKnown) {
    DefensePotion::known = newKnown;
}

bool PoisonPotion::getKnown() const {
    return PoisonPotion::known;
}

void PoisonPotion::setKnown(bool newKnown) {
    PoisonPotion::known = newKnown;
}

bool WeakPotion::getKnown() const {
    return WeakPotion::known;
}

void WeakPotion::setKnown(bool newKnown) {
    WeakPotion::known = newKnown;
}

bool BrittlePotion::getKnown() const {
    return BrittlePotion::known;
}

void BrittlePotion::setKnown(bool newKnown) {
    BrittlePotion::known = newKnown;
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

string HealthPotion::getName() const { return getKnown()? "BH" : "unknown"; }
string AttackPotion::getName() const { return getKnown()? "BA" : "unknown"; }
string DefensePotion::getName() const { return getKnown()? "BD" : "unknown"; }
string PoisonPotion::getName() const { return getKnown()? "LH" : "unknown"; }
string WeakPotion::getName() const { return getKnown()? "LA" : "unknown"; }
string BrittlePotion::getName() const { return getKnown()? "LD" : "unknown"; }

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
static const float DROW_POTION_AMP = 1.5f;

void HealthPotion::affect(Entity &e) {
    try {
        try {
            Drow &drow {dynamic_cast<Drow&>(e)};
            drow.setHP(drow.getHP() + static_cast<int>(DELTA_HP * DROW_POTION_AMP));
        }
        catch(const bad_cast &ex) {
            Character &character {dynamic_cast<Character&>(e)};
            character.setHP(character.getHP() + DELTA_HP);
        }
        setKnown(true);
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
        try {
            Drow &drow {dynamic_cast<Drow&>(e)};
            drow.changeDeltaATK(static_cast<int>(DELTA_ATK * DROW_POTION_AMP));
        }
        catch(const bad_cast &ex) {
            Character &character {dynamic_cast<Character&>(e)};
            character.changeDeltaATK(DELTA_ATK);
        }
        setKnown(true);
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
        try {
            Drow &drow {dynamic_cast<Drow&>(e)};
            drow.changeDeltaDEF(static_cast<int>(DELTA_DEF * DROW_POTION_AMP));
        }
        catch(const bad_cast &ex) {
            Character &character {dynamic_cast<Character&>(e)};
            character.changeDeltaDEF(DELTA_DEF);
        }
        setKnown(true);
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
        try {
            Drow &drow {dynamic_cast<Drow&>(e)};
            drow.setHP(static_cast<int>(drow.getHP() - DELTA_HP * DROW_POTION_AMP));
        }
        catch(const bad_cast &ex) {
            Character &character {dynamic_cast<Character&>(e)};
            character.setHP(character.getHP() - DELTA_HP);
        }
        setKnown(true);
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
        try {
            Drow &drow {dynamic_cast<Drow&>(e)};
            int delta = drow.getATK() - max(0, static_cast<int>(drow.getATK() - DELTA_ATK * DROW_POTION_AMP));
            drow.changeDeltaATK(-delta);
        }
        catch(const bad_cast &ex) {
            Character &character {dynamic_cast<Character&>(e)};
            int delta = character.getATK() - max(0, character.getATK() - DELTA_ATK);
            character.changeDeltaATK(-delta);
        }
        setKnown(true);
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
        try {
            Drow &drow {dynamic_cast<Drow&>(e)};
            int delta = drow.getDEF() - max(0, static_cast<int>(drow.getDEF() - DELTA_DEF * DROW_POTION_AMP));
            drow.changeDeltaATK(-delta);
        }
        catch(const bad_cast &ex) {
            Character &character {dynamic_cast<Character&>(e)};
            int delta = character.getDEF() - max(0, character.getDEF() - DELTA_DEF);
            character.changeDeltaATK(-delta);
        }
        setKnown(true);
        setStatus(Entity::Status{
            .action = Entity::Action::KILL_ME,
            .data = monostate{},
        });
        notifyObservers();
    }
    catch(const bad_cast &ex) {}
}

// character.setHP(max(1, character.getHP() - 10));
