#include "races.h"
#include <memory>
#include <cmath>


// HOW TO DO CUSTOM POTION EFFECT PLS HELP!!!

void Vampire::attack(Tile& target) {
    const int DWARF_DAMAGE = 5;
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    std::shared_ptr<Dwarf> d = std::dynamic_pointer_cast<Dwarf>(c);
    if (!c) return; // not a character
    int damage = ceil((100/(100 + c->getDEF())) * atk);
    c->setHP(c->getHP() - damage); // do damage
    if (d != nullptr) {
        c->setHP(c->getHP() - DWARF_DAMAGE); // reverse ability OOF
    } else {
        c->setHP(c->getHP() + DWARF_DAMAGE);
    }
    if (c->getHP() <= 0) { target.setEntity(nullptr);} // kill if dead
}

// NEED TO DO SOMETHING ABOUT THE FUCKING +5 HP EVERY TURN


void Goblin::attack(Tile& target) {
    const int GOBLIN_FILTHY_CAPITALIST_BONUS = 5;
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    std::shared_ptr<Halfling> h = std::dynamic_pointer_cast<Halfling>(c);
    if (!c) return; // not a character
    int damage = ceil((100/(100 + c->getDEF())) * atk);
    c->setHP(c->getHP() - damage); // do damage
    if (c->getHP() <= 0) {
        target.setEntity(nullptr);
        setGold(getGold() + GOBLIN_FILTHY_CAPITALIST_BONUS);
    }
}


// HUMAN is DEFAULT

// DWARF is DEFUALT

// ELF
void Elf::attack(Tile& target) {
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    std::shared_ptr<Drow> d = std::dynamic_pointer_cast<Drow>(c);
    int atk_count = (!d) ? 2 : 1;
    for (int i = 0; i < atk_count; ++i) {
        if (!c) return; // not a character
        int damage = ceil((100/(100 + c->getDEF())) * atk);
        c->setHP(c->getHP() - damage); // do damage
        if (c->getHP() <= 0) {target.setEntity(nullptr);}
    }
}

// ORC

void Orc::attack(Tile& target) {
    std::shared_ptr<Entity> t = target.getEntity(); // grab the entity
    std::shared_ptr<Character> c = std::dynamic_pointer_cast<Character>(t); //get character data
    std::shared_ptr<Goblin> g = std::dynamic_pointer_cast<Goblin>(c);
    if (!c) return; // not a character
    int damage = ceil((100/(100 + c->getDEF())) * atk);
    if (!g) {
        damage += damage / 2;
    }
    c->setHP(c->getHP() - damage); // do damage
    if (c->getHP() <= 0) {target.setEntity(nullptr);}
}

// MERCHANT

void Merchant::attack(Tile& target) {
    if (!isPissed) return;
    Enemy::attack(target);
}

void Merchant::togglePissed() {
    isPissed = !isPissed;
}

// dragon do not do much

// hafling // not unique

CharacterDefaults getCharDefs(Race race) {
    switch (race) {
        case Race::SHADE:
        return {125, 25, 25, 100, 0};
        case Race::DROW:
        return {150, 25, 15, 100, 0};
        case Race::VAMPIRE:
        return {50, 25, 25, 100, 0};
        case Race::TROLL:
        return {120, 25, 15, 100, 0};
        case Race::GOBLIN:
        return {110, 15, 20, 100, 0};
        case Race::HUMAN:
        return {140, 20, 20, 50, 4};
        case Race::DWARF:
        return {100, 20, 30, 50, 0};
        case Race::ELF:
        return {140, 30, 10, 50, 0};
        case Race::ORC:
        return {180, 30, 25, 50, 0};
        case Race::DRAGON:
        return {150, 20, 20, 50, 0};
        case Race::MERCHANT:
        return {30, 70, 5, 50, 0};
        case Race::HALFLING:
        return {100, 15, 20, 50, 0};
    }
}